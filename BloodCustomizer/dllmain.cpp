// dllmain.cpp : Defines the entry point for the DLL application.
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "plugin/PatternSolver.h"

#ifdef HOOKPLUGIN
#include "PluginInfo.h"
#include "SDK.h"
#endif 

#include "BloodCustomizer.h"

using namespace Memory::VP;


int64 pat = 0;
int64 pat2 = 0;

void Init()
{
    Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
    settings.Init();

    InjectHook(pat, tramp->Jump(&PlayerInfoEx::SetColor));
    InjectHook(pat2, tramp->Jump(&PlayerInfoEx::SetColor));
}

bool ValidateGameVersion()
{
    pat = PatternSolver::GetPattern("E8 ? ? ? ? FF C7 EB BD 4C 89 65 D8 4C 89 65 E0 48 8D 55 D8", 0);
    pat2 = PatternSolver::GetPattern("E8 ? ? ? ? FF C7 EB DA 4C 89 65 C8 4C 89 65 D0", 0);
    pSetColor = PatternSolver::GetPattern("48 89 5C 24 ? 57 48 83 EC 40 48 63 59 30 45 33 C9 4D 8B D8 48 8B F9 85 DB 7E 1F 4C 8B 51 28 90 4B 8D 0C 49 49 39 14 CA 4D 8D 04 CA 0F 84 ? ? ? ? 41 FF C1 44 3B CB", 0);


    if (!pat || !pat2 || !pSetColor)
    {
        MessageBoxA(0, "Failed to find patterns!\nThis might indicate that the game version is not supported or the plugin has not been updated.", "MK11.BloodCustomizer", MB_ICONERROR);
        return false;
    }

    return true;
}
#ifdef HOOKPLUGIN
// Plugin name to use when loading and printing errors to log
extern "C" PLUGIN_API const char* GetPluginName()
{
    return "Blood Customizer (1.0)";
}

// Hook project name that this plugin is compatible with
extern "C" PLUGIN_API const char* GetPluginProject()
{
    return "MK11HOOK";
}

// GUI tab name that will be used in the Plugins section
extern "C" PLUGIN_API const char* GetPluginTabName()
{
    return "Blood Customizer";
}

// Initialization
extern "C" PLUGIN_API void OnInitialize()
{
    MK11HOOKSDK::Initialize();
    if (ValidateGameVersion())
        Init();
}

// Shutdown
extern "C" PLUGIN_API void OnShutdown()
{

}

// Called every game tick
extern "C" PLUGIN_API void OnFrameTick()
{

}

// Called on match/fight start
extern "C" PLUGIN_API void OnFightStartup()
{

}

// Tab data for menu, remove this if you don't want a plugin tab
extern "C" PLUGIN_API void TabFunction()
{
    if (!MK11HOOKSDK::IsOK())
        return;

    MK11HOOKSDK::ImGui_Checkbox("Enable##blc", &settings.m_bEnable);

    MK11HOOKSDK::ImGui_Separator();
    MK11HOOKSDK::ImGui_Text("Blood FX is reloaded on each match, not during gameplay.");
    MK11HOOKSDK::ImGui_Separator();
    MK11HOOKSDK::ImGui_Text("Blood Color (Alpha is ignored)");
    if (MK11HOOKSDK::ImGui_ColorEdit4("Pick RGB", settings.m_fColors))
    {
        settings.m_colors[0] = (int)(settings.m_fColors[0] * 255.0f);
        settings.m_colors[1] = (int)(settings.m_fColors[1] * 255.0f);
        settings.m_colors[2] = (int)(settings.m_fColors[2] * 255.0f);
    }

    if (MK11HOOKSDK::ImGui_Button("Save Settings"))
    {
        settings.Save();
    }

}

#endif


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
#ifndef HOOKPLUGIN
        if (ValidateGameVersion())
            Init();
#endif
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

