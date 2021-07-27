// Why header files?
// During programming we call APIs provided by SDK. So for compiler to convert from high level to machine level
// which are not defined by you but consume by you to tell compiler that such kind of function will be called
// in the code and it will use APIs compiled code during compilation process.
// coco.h - in Mac
#include <windows.h>
#include <tchar.h>

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
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

// Global Variable Declarations

// Entry point Functions
// WINMAIN name is must
// It is internally WINMAINCRTSTARTUP
// This function is also pre-decided by OS
// Therefore OS decided parameters and OS decided return value.

// Callback functions are re-entrants function but entry-point function gets called only once.
//Parameters
// 1. hInstance - Unique unsigned ID of current instance
// 2. hPrevInstance - Null (Since Windows 3.1 due to pre-emptive multitasking)
// 3. lpszCmdLine  - Command-line arguments (sz :- Zero terminated string)(Long Pointer to String)
// 4. iCmdShow - How to show the Window (Minimized, Maximized)
// WINAPI :- _far_pascal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Local Variable Declarations
    
    // Structure to hold the Windows properties
    WNDCLASSEX wndclass;
    HWND hwnd;
    // 
    MSG msg;
    TCHAR szAppName[] = TEXT("MyWindow");

    // Code

    // Step 1 - Initialize WNDCLASSEX structure
    // Size of Window structure in bytes cb:- count of Bytes
    wndclass.cbSize = sizeof(WNDCLASSEX);
    // class style of the window
    // CS : Class Style
    // HREDRAW: Horizontal ReDraw
    // VREDRAW: Vertical ReDraw
    // Why we need Redraw? Will get during PAINT message
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
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
        // OS is handling some default message in DefWindowProc
        // Check where is the message happen on the window e.g. clicking on close button window in Left Mouse button down
        // But the co-ordinate where the click is happened is close button.
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hThread1 = NULL;
    static HANDLE hThread2 = NULL;
    // Code
    switch (iMsg)
    {
        case WM_CREATE:
		// (LPVOID) hwnd : This will act as parameter to your ThreadProc
            hThread1 = CreateThread(
                NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProcOne, (LPVOID) hwnd, 0, NULL);
            //Should contain error checking for hThread1
            hThread2 = CreateThread(
                NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProcTwo, (LPVOID) hwnd, 0, NULL);
            // Should contain error checking for hThread2
            
        break;
        case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("I am Thread no 4"), TEXT("Message"), MB_OK);
		break;
        case WM_DESTROY:
            CloseHandle(hThread1);
            CloseHandle(hThread2);
         	PostQuitMessage(0);
         break;
    
        default:
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
    // variable declarations
    HDC hdc = NULL;
    TCHAR str[255];
    long i;
    
    //Code
    hdc = GetDC((HWND) param);
	SetBkColor(hdc, RGB(0,0,0));
	SetTextColor(hdc, RGB(0,255,0));
	for (i = 0; i < 2147483647; i++)
	{
		/* code */
		wsprintf(str, TEXT("Incrementing Order: %ld"), i);
		TextOut(hdc, 5, 5, str, (int) _tcslen(str));
	}
	ReleaseDC((HWND) param, hdc);

	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
    // variable declarations
    HDC hdc = NULL;
    TCHAR str[255];
    long i;
    
    //Code
    hdc = GetDC((HWND) param);
	SetBkColor(hdc, RGB(0,0,0));
	SetTextColor(hdc, RGB(255,0,0));
	for (i = 2147483647; i >= 0 ; i--)
	{
		/* code */
		wsprintf(str, TEXT("Decrementing Order: %ld"), i);
		TextOut(hdc, 5, 25, str, (int) _tcslen(str));
	}
	ReleaseDC((HWND) param, hdc);

	return (0);
}

