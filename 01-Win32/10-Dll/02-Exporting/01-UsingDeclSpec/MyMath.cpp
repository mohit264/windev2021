#pragma once
#include<Windows.h>

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
    // code
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        /* code */
        break;
        case DLL_THREAD_ATTACH:
        /* code */
        break;
        case DLL_PROCESS_DETACH:
        /* code */
        break;
        case DLL_THREAD_DETACH:
        /* code */
        break;
    
    default:
        break;
    }
    return TRUE;
}

// Extern C is required for Explicit linking
extern "C" __declspec(dllexport) int MakeCube(int num)
{
    //code
    int cube = num * num * num;

    return cube;
}
