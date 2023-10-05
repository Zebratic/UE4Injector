# UE4Injector
 Unreal Engine 4 vulnerability, that allows you to run shellcode directly into the target game process.

# NO LONGER IN DEVELOPMENT
This source code is from 2018, but is still functional in 2022, for most UE4 games that have not implemented a manual patch for the vulnerability.
Do not contact me asking me to update this library, I will NOT be continuing to work on this project, however, you are freely to use my work, as long as im credited.

# Understanding the code
- I have been somewhat decent in writing a few comments about what the code does, and is doing.
- Its not perfect, but it is simply to get a quick understanding on how the vulnerability works, and how its utilized.
- Sorry that i was too lazy to not write comments in **"map.cpp"**, i appearently didnt do so in 2018.

# Compiling
- Recommended to compile in **Visual Studio 2019-2022**
- Make sure you have set **C++ Language Standard** to **"Default (ISO C++14 Standard)"**
- Make sure you have set **Enable Incremental Linking** to **"Yes"**
- Compile in **Release** as **x64**
- Output executable can be found in: ....**\x64\Release\UE4Injector.exe**
- Only the executable is needed for it to run successfully, any other file is temporary files and are not needed.

# Usage
1. **Executable REQUIRES Admin Privileges!**
2. Run ``UE4injector.exe (ProcesName.exe) (SurfaceLibrary.dll) (CustomLibrary.dll)`` in either cmd or a bat file.
- Example: ``UE4injector.exe FortniteClient-Win64-Shipping.exe dxgi.dll cheat.dll``
- You can also build a shell around the injector and use it as a loader, as most game cheats are doing.
- Such as a simple exe running the code like **"system("UE4injector.exe FortniteClient-Win64-Shipping.exe dxgi.dll cheat.dll");"** in a C++ binary.

# Note
- Make sure the DLL your loading are checking for the **"DWORD ul_reason_for_call"** parameter.
- UE4Injector will set **"ul_reason_for_call"** to **"DLL_PROCESS_ATTACH"**, _**NOT A STRING**_

### DLL Example:
```cpp
#include <windows.h>
#include <stdlib.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // RUN YOUR CODE HERE
    }

    return TRUE;
}
```

# main.cpp logs
```
Github: https://github.com/Zebratic
Discord: Zebratic#6969 <@811372110157053953>

Zebratic's notes here;
I just wanna say that this project started as a simple joke and a tiny vulnerability in Unreal Engine 4
The vulnerability to load our own shellcode and execute within the games process is fully undetected by most anti cheats
and can be used to load cheats, mods, malware, what ever you might want to load into a game.
This project took probably over 30+ hours to get to the state of where it is now.
The source code is PRIVATE, for legal reasons!

Epic Games, Unreal Engine development team have already been sent this PoC source code so that they can patch their vulnerability.
But in response to my $5000 bug bounty i got notified that they WONT patch this vulnerability as it will break alot of games running on their engine.
But they have added checks to see if there has been injected any shell code into the game process.
However, this can EASILY be bypassed as shown in "hijack.cpp" at line 71!
Do what you want with this source code, but dont use it for bad intentions.
For the retards reading this, Build the project in Release x64, and you should not have any errors upon compiling.

Thanks again
Zebratic, the 18 year old danish Cyber Security Specialist


2022 note: I came back to this source code, and i checked a bit up on it for a buddy asking for help, Ectophile#9906, your welcome.
I can confirm that this still fully works, but still needs a hijacked driver to run, but it all still fully works on most games.
Detection wise im not sure how it will be after 4 years of Epic Games' notice of the vulnerability.
But so far, im making this PoC source code PUBLIC on github available for everyone to use.
USE AT OWN RISK!!!!!! I AS IN ZEBRATIC IS IN NO WAY RESPONSIBLE IF ANY DAMAGE WAS DONE TO YOUR PC/GAME/ACCOUNT!!!!!
```

## USE AT OWN RISK
_**I as in Zebratic, is in no way responsible for any damage that could have been done to your PC/Game/Account!**_
