// dllmain.cpp : Defines the entry point for the DLL application.
#include "ProfileLayer.h"
#include "AccountSettingsLayer.h"
#include "MinHook.h"
#include <cocos2d.h>

size_t DiscordButton::base = reinterpret_cast<size_t>(GetModuleHandle(0));

DWORD WINAPI my_thread(void* hModule) {

    /*AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stderr);*/

    MH_Initialize();
    ProfileLayer::mem_init();
    AccountSettingsLayer::mem_init();
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}  

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

