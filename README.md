# UE4Injector
 Unreal Engine 4 vulnerability, that allows you to run shellcode directly into the target game process.

# NO LONGER IN DEVELOPMENT
This source code is from 2018, but is still functional in 2021, for most UE4 games that have not implemented a manual patch for the vulnerability.
I will NOT be continuing to work on this project, however, you are freely to use my work, as long as im credited.

# Usage
1. Executable REQUIRES Admin privileges!
2. Run ``UE4injector.exe (ProcesName.exe) (SurfaceLibrary.dll) (CustomLibrary.dll)``
- Example: ``UE4injector.exe FortniteClient-Win64-Shipping.exe dxgi.dll cheat.dll``

# Note
Make sure the DLL your loading are checking for a ul_reason_for_call.
UE4Injector will give the call reason: DLL_PROCESS_ATTACH
DLL Example:
```
#include <windows.h>
#include <stdlib.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // RUN YOUR CODE HERE
    }

    return TRUE;
}
```


## USE AT OWN RISK
I as in Zebratic, is in no way responsible for any damage that could have been done to your PC/Game/Account!
