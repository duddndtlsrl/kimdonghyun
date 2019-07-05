#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
int y = 100;
int rad = 500;
int centerX = 0;
int centerY = 0;
int secDgree = 0;
int timeNumX = 0;
int timeNumY = 0;
TCHAR sTime[128];
int secX = 0;
int secY = 0;
SYSTEMTIME st;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	//static char sTime[128];
	static TCHAR sTime[128];

	switch (iMessage)
	{
	case WM_CREATE:
		centerX = x + (rad / 2);
		centerY = y + (rad / 2);
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		GetLocalTime(&st);
		secDgree = st.wSecond * 6;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, centerX - (rad / 2), centerY - (rad / 2), centerX + (rad / 2), centerY + (rad / 2));

		for (int i = 0; i < 13; i++)
		{
			wsprintf(sTime, TEXT("%d"), i);
			timeNumX = centerX + 250 * cosf((270 + 30 * i) * 3.14 / 180);
			timeNumY = centerY + 250 * sinf((270 + 30 * i) * 3.14 / 180);

			TextOut(hdc, timeNumX, timeNumY, sTime, lstrlen(sTime));
		}

		//초침
		MoveToEx(hdc, centerX, centerY, NULL);

		//중심점의 위치에서 반지름 길이만큼의 위치에 있는 좌표 x, y
		//시간이 변할때마다 갱신된다.
		secX = centerX + 250 * cosf((270 + secDgree) * 3.14 / 180);
		secY = centerY + 250 * sinf((270 + secDgree) * 3.14 / 180);
		LineTo(hdc, secX, secY);
		
		wsprintf(sTime, TEXT("지금 시간은 %d:%d:%d입니다."),
			st.wHour, st.wMinute, st.wSecond);

		TextOut(hdc, 250, 650, sTime, lstrlen(sTime));
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
