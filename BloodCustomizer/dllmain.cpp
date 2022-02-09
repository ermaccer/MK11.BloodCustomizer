// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MemoryMgr.h"
#include "Trampoline.h"
#include "mk10utils.h"
#include "BloodCustomizer.h"

using namespace Memory::VP;

void Init()
{
    Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
    InjectHook(_addr(0x140E4DFCA), tramp->Jump(SetColor));
    InjectHook(_addr(0x140E4E00D), tramp->Jump(SetColor));

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

