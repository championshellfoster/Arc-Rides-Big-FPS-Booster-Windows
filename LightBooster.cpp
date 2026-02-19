#include <Windows.h>
#include <Renderer.hpp>
#include <Hooks.hpp>

static bool isInitialized = false;

void OnDllAttach()
{
    if (!isInitialized) {
        RendererInitialize();
        HooksInitialize();

        isInitialized = true;
    }
}

void OnDllDetach()
{

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OnDllAttach, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            if (lpReserved == nullptr)
                OnDllDetach();
            break;
    }
    return TRUE;
}