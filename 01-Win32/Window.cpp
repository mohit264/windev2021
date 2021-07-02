#include <Windows.h>

// Global Function declaration --declaring it 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

// Global variable declaration 

//Entry point Function --calling it 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local variable declarations 
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	//Shaila- empty array bracket defines an array and TEXT MACRO 
	TCHAR szAppName[] = TEXT("My Window");

	
	//Declaring Class ...
	//Code Sizeof is an operator 
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc; 
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0; 
	wndclass.hInstance = hInstance;
	//Using the First API of WINDOWS 
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Registring Class...  
	RegisterClass(&wndclass);

	//Create Window in Memory
	// Creating windows handle.. 
	hwnd = CreateWindow(szAppName,
		TEXT("SHAILA:My First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Showing Window..

	ShowWindow(hwnd, iCmdShow);

	//Colouring Window.. 
	UpdateWindow(hwnd);

	//Heart of an application.. Message Loop 

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

	//Writing Body of CAllBAck function.. 
	LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
		//Code
	{
		switch (iMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;

		}
		return(DefWindowProc(hwnd, iMsg, wParam, lParam));

	}
}


