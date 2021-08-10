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
// Removed __declspec(dllexport) as it is not needed and taken care by DEF file
// Linker read all the functions in DEF and create .exp file for Export Function table
// to be added in DLL's export function

//link MyMath.obj /DLL /DEF:MyMath.def user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
extern "C" int MakeCube(int num)
{
    //code
    int cube = num * num * num;

    return cube;
}
