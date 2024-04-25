#include <windows.h>
#include <detours.h>

#include <iostream>
#include <algorithm>

#include "memcury.h"
#include "structs.h"
#include "natives.h"
#include "commands.h"
#include "detours.h"

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE* File;
    freopen_s(&File, "CONOUT$", "w", stdout);

    if (Natives::Init() && Detours::Init())
    {
        EnableConsole();
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}