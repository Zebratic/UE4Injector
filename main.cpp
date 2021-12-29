#include "stdafx.h"

// Github: https://github.com/Zebratic
// Discord: Zebratic#6969 <@811372110157053953>

// Zebratic's notes here;
// I just wanna say that this project started as a simple joke and a tiny vulnerability in Unreal Engine 4
// The vulnerability to load our own shellcode and execute within the games process is fully undetected by most anti cheats
// and can be used to load cheats, mods, malware, what ever you might want to load into a game.
// This project took probably over 30+ hours to get to the state of where it is now.
// The source code is PRIVATE, for legal reasons!

// Epic Games, Unreal Engine development team have already been sent this PoC source code so that they can patch their vulnerability.
// But in response to my $5000 bug bounty i got notified that they WONT patch this vulnerability as it will break alot of games running on their engine.
// But they have added checks to see if there has been injected any shell code into the game process.
// However, this can EASILY be bypassed as shown in "hijack.cpp" at line 68!
// Do what you want with this source code, but dont use it for bad intentions.
// For the retards reading this, Build the project in Release x64, and you should not have any errors upon compiling.

// Thanks again
// Zebratic, the 15 year old danish Cyber Security Specialist


// 2021 note: I came back to this source code, and i checked a bit up on it for a buddy asking for help, Ectophile#9906, your welcome.
// I can confirm that this still fully works, but still needs a hijacked driver to run, but it all still fully works on most games.
// Detection wise im not sure how it will be after 4 years of Epic Games' notice of the vulnerability.
// But so far, im making this PoC source code PUBLIC on github available for everyone to use.
// USE AT OWN RISK!!!!!! I AS IN ZEBRATIC IS IN NO WAY RESPONSIBLE IF ANY DAMAGE WAS DONE TO YOUR PC/GAME/ACCOUNT!!!!!

INT main(INT argc, LPCSTR *argv) {
	printf("Zebratic#6969's UE4 Dynamic Link Library Injector\n");
	printf("Made for educational purposes to showcase different vulnerabilities in Unreal Engine 4\n\n");
	printf("----------------------[ UE4INJECTOR ]----------------------\n");
	if (argc < 4) {
		printf("[!] MISSING ARGUMENTS! [!]\n");
		printf("[!] Just use your brain duh?! [!]\n");
		Sleep(5000);
		return 1;
	}

	// Load ntdll library and find module addresses
	if (!utils::Setup()) {
		errorf("Failed to finish library setup!\n");
		Sleep(5000);
		return 1;
	}

	// Simple check if the process is running
	utils::Process process(StrToWStr(argv[1]));
	if (!process.Valid()) {
		errorf("Failed to find game process!\n");
		Sleep(5000);
		return 1;
	}

	// Extend map to the game process (Prepare process for injection)
	auto entry = Map::ExtendMap(process, StrToWStr(argv[3]), StrToWStr(argv[2]));
	if (!entry) {
		errorf("Failed to extend map!\n");
		Sleep(5000);
		return 1;
	}

	// Hijack PeekMessageW function to inject our own code
	if (!Hijack::HijackViaHook(process, entry, L"user32.dll", "PeekMessageW")) {
		errorf("Failed to hijack with the hook!\nHas the driver been loaded successfully?\n");
		Sleep(5000);
		return 1;
	}
	
	// SUCCESS!!! You have now loaded your own Dynamic Link Library into your targeted UE4 process! Good Job!
	// Now we return 0, aka close the injector.
	return 0;
}