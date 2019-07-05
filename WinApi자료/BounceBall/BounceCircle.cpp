#include<windows.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BounceCircle");
void DrawCircle(HDC hdc, int x, int y);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int x = 100;
int y = 550;
int speed_x = 30;
int speed_y = 30;
int rad = 50;

RECT rc = { 0, 0, 700, 700 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, TimeProc);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		DrawCircle(hdc, x, y);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

	x += speed_x;
	y += speed_y;

	if (x >= rc.right - rad)
	{
		x = rc.right - rad;

		speed_x = -speed_x;
	}
	else if (x <= rc.left + rad)
	{
		x = rc.left + rad;

		speed_x = -speed_x;
	}

	if (y >= rc.bottom - rad)
	{
		y = rc.bottom - rad;

		speed_y = -speed_y;
	}
	else if (y <= rc.top + rad)
	{
		y = rc.top + rad;

		speed_y = -speed_y;
	}
	


	InvalidateRect(hWnd, NULL, TRUE);
}

void DrawCircle(HDC hdc, int x, int y)
{
	Ellipse(hdc, x - rad, y - rad, x + rad, y + rad);
}
