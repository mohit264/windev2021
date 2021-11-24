#include<Windows.h>
#include"MyDllServer.h"

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


extern "C" int SumOfTwoIntergers(int num1, int num2)
{
    return num1 + num2;
}