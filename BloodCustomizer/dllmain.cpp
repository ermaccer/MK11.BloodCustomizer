// dllmain.cpp : Defines the entry point for the DLL application.
#include "MemoryMgr.h"
#include "Trampoline.h"
#include "mk10utils.h"
#include "BloodCustomizer.h"

using namespace Memory::VP;
// todo: patterns since its small!

void Init()
{
    Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
    settings.Init();

    InjectHook(_addr(0x140E4DFCA), tramp->Jump(&PlayerInfo::SetColor));
    InjectHook(_addr(0x140E4E00D), tramp->Jump(&PlayerInfo::SetColor));
}

bool ValidateGameVersion()
{
    char* gameName = (char*)_addr(0x142600D98);

    if (strcmp(gameName, "Mortal Kombat 11") == 0)
        return true;
    else
    {
        MessageBoxA(0, "Invalid game version!\nBloodCustomizer only supports latest Steam executable, not DirectX12 one.\n\n"
            "If you still cannot run the plugin and made sure that the game is updated, BloodCustomizer needs to be updated.", 0, MB_ICONINFORMATION);
        return false;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (ValidateGameVersion())
            Init();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

