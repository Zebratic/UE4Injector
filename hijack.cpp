#include "stdafx.h"

#pragma warning (disable : 6271) // mute unimportant warnings
#pragma warning (disable : 4474) // mute unimportant warnings

namespace Hijack {
	BOOLEAN HijackViaHook(utils::Process &process, PVOID entry, LPCWSTR moduleName, LPCSTR functionName) {

		PBYTE remoteModuleBase = NULL;
		DWORD remoteModuleSize = 0;
		if (process.Module(moduleName, &remoteModuleBase, &remoteModuleSize) != ERROR_SUCCESS) {
			errorf("RemoteModuleBase Error", moduleName);
			return FALSE;
		}

		// Im using LoadLibrary, and it was undetected for UE4 games using Easy Anti Cheat and BattleEye at this time (2018-2020+?)
		auto module = LoadLibrary(moduleName);
		if (!module) {
			errorf("LoadLibrary Error", moduleName);
			return FALSE;
		}

		// Find our own function address so we can inject it into the "remoteFunction"
		auto function = reinterpret_cast<PBYTE>(GetProcAddress(module, functionName));
		if (!function) {
			errorf("GetProcAddress Error", moduleName, functionName);
			return FALSE;
		}

		auto remoteFunction = remoteModuleBase + (function - reinterpret_cast<PBYTE>(module));

		// Load our custom shellcode (this is the vulnerability)
		BYTE shellcode[] = { 0x00, 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x10, 0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x50, 0x08, 0x48, 0x83, 0xEC, 0x28, 0x48, 0xBA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x15, 0x02, 0x00, 0x00, 0x00, 0xEB, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x28, 0x48, 0x31, 0xC0, 0xC6, 0x05, 0xAE, 0xFF, 0xFF, 0xFF, 0x01, 0xC3 };
		*reinterpret_cast<PVOID *>(&shellcode[3]) = remoteFunction;
		process.Read(&shellcode[13], remoteFunction, sizeof(ULONG64));
		process.Read(&shellcode[26], remoteFunction + sizeof(ULONG64), sizeof(ULONG64));
		*reinterpret_cast<PVOID *>(&shellcode[60]) = entry;

		// Prepare our shellcode payload
		auto mappedShellcode = reinterpret_cast<PBYTE>(process.Alloc(sizeof(shellcode), PAGE_EXECUTE_READWRITE));
		if (!mappedShellcode) {
			errorf("Shellcode Error");
			return FALSE;
		}

		// Execute out shellcode payload into the game process
		process.Write(mappedShellcode, shellcode, sizeof(shellcode));

		BYTE jump[14] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00 };
		*reinterpret_cast<PVOID *>(&jump[6]) = mappedShellcode + 1;

		// Make sure we have permission within the process to make our changes (REASON THIS NEEDS ADMIN!!!!!)
		DWORD protect = PAGE_EXECUTE_READWRITE;
		process.Protect(remoteFunction, 2 * sizeof(ULONG64), &protect);

		// Write a jump opcode to the game process to skip directly to our own payload
		process.Write(remoteFunction, jump, sizeof(jump));

		for (auto functionBytes = 0ULL;; Sleep(1)) {
			if (process.Read(&functionBytes, remoteFunction + 6, sizeof(functionBytes)) != ERROR_SUCCESS) { // Check if it was successful to inject our payload
				errorf("RemoteBytes Error", remoteFunction + 6);
				return FALSE;
			}

			if (functionBytes != *reinterpret_cast<PULONG64>(&jump[6])) {
				break;
			}
		}

		// This might be important in future UE4 games, you can try commenting this out and test if it makes any changes
		process.Protect(remoteFunction, sizeof(jump), &protect); // EDIT: REMOVING THIS CAN CAUSE FALSE BANS ON SOME GAMES! (RUST, R6S, NOT FORTNITE YET?)

		for (BYTE status = 0;; Sleep(1)) {
			if (process.Read(&status, mappedShellcode, sizeof(status)) != ERROR_SUCCESS) {
				errorf("MappedShellcode Error", mappedShellcode);
				return FALSE;
			}

			if (status) {
				break;
			}
		}

		// Free our shellcode, since we dont need it anymore
		process.Free(mappedShellcode);

		return TRUE;
	}
}