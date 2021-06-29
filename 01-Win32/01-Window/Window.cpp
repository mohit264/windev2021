// Why header files?
// During programming we call APIs provided by SDK. So for compiler to convert from high level to machine level
// which are not defined by you but consume by you to tell compiler that such kind of function will be called
// in the code and it will use APIs compiled code during compilation process.
// coco.h - in Mac
#include <windows.h>

// Global Functions Declarations

// Declaring the function / prototype to let compiler know that body of this function will come later
// When there are several function it is good practice to create separate header file for them.

// This is callback function in event-driven architecture
// This should be in special addresss (Far segment) CALLBACK is typedef of _far_pascal
// WndProc name is by convention not the compulsion
// std calling convention or pascal calling convention which pass the parameters from right to left

// Parameters
// 1. HWND is internally unique unsigned 32 int
// Handle to Window
// What is handle? 
// Handles are keys in the OS tables which represents which resources are currently active in memory.
// So if  there are 50 windows open in desktop there are 50 handles(keys) present in Windows assuming
// 50 different application

// 2. UINT -- Event converted into unique message id 
// Why  event is sent as in integer because event is coming from hardware device which is identified as integer.

// 3,4. W(ord)PARAM and L(ong)PARAM (Message Parameters)
// Description about the event, who is event sender means every message has it's own attributes.
// if the less attributed message i.e. (16-bit) and if there more attributes to the message.
// then it can be passed from LPARAM.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations

// Entry point Functions
// WINMAIN name is must
// It is internally WINMAINCRTSTARTUP
// This function is also pre-decided by OS
// Therefore OS decided parameters and OS decided return value.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Local Variable Declarations
    
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyWindow");

    // Code

    // Step 1 - Initialize WNDCLASSEX structure
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // Step 2 - Register WNDCLASSEX structure
    RegisterClassEx(&wndclass);

    // Step 3 - Create Window in Memory
    hwnd = CreateWindow(szAppName, 
            TEXT("MVD:My First Window!"), 
            WS_OVERLAPPEDWINDOW, 
            CW_USEDEFAULT, 
            CW_USEDEFAULT, 
            CW_USEDEFAULT, 
            CW_USEDEFAULT, 
            NULL, 
            NULL, 
            hInstance, 
            NULL);

    // Step 4 - Show Window
    ShowWindow(hwnd, iCmdShow);

    // Paint the back of this window
    UpdateWindow(hwnd);

    // Message Loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // Code
    switch (iMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
