# UE4Injector
 Unreal Engine 4 vulnerability, that allows you to run shellcode directly into the target game process.

# NO LONGER IN DEVELOPMENT
This source code is from 2018, but is still functional in 2021, for most UE4 games that have not implemented a manual patch for the vulnerability.
Do not contact me asking me to update this library, I will NOT be continuing to work on this project, however, you are freely to use my work, as long as im credited.

# Compiling
- Recommended to compile in Visual Studio 2019-2022
- Compile in **Release** as **x64**
- Output executable can be found in: ....\x64\Release\UE4Injector.exe
- Only the executable is needed for it to run successfully, any other file is temporary files and are not needed.

# Usage
1. Executable REQUIRES Admin privileges!
2. Run ``UE4injector.exe (ProcesName.exe) (SurfaceLibrary.dll) (CustomLibrary.dll)``
- Example: ``UE4injector.exe FortniteClient-Win64-Shipping.exe dxgi.dll cheat.dll``

# Note
- Make sure the DLL your loading are checking for the "DWORD ul_reason_for_call" parameter.
- UE4Injector will set "ul_reason_for_call" to "DLL_PROCESS_ATTACH", NOT A STRING

### DLL Example:
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
