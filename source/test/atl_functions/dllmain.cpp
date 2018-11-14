// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#ifdef _USRDLL

#pragma comment(lib, "cutest.lib")

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif // #ifdef _USRDLL
