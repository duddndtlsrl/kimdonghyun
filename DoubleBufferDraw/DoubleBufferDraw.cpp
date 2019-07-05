#include "defines.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWnd;
LPCTSTR lpszClass = TEXT("Hello World!!");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

HDC			g_MemDC[3];
HBITMAP		g_hBitmap[3];	//0 Back 1 BackGround 2 char
HBITMAP		g_hOld[3];
int			x = 500;
int			y = 300;

enum PLAYER_STATE
{
	PLAYER_STATE_WAIT,
	PLAYER_STATE_MOVE,
	PLAYER_STATE_JUMP
};

#define PI 3.141592f
POINT m_ptJumpPos;
DWORD m_dwJumpCount = 0;

PLAYER_STATE m_eState = PLAYER_STATE_WAIT;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:		
		SetTimer(hWnd, 1, 10, NULL);
		hdc = GetDC(hWnd);
		g_MemDC[0] = CreateCompatibleDC(hdc);
		g_hBitmap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitmap[0]);

		g_MemDC[1] = CreateCompatibleDC(g_MemDC[0]);
		g_hBitmap[1] = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0
			, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitmap[1]);

		g_MemDC[2] = CreateCompatibleDC(g_MemDC[0]);
		g_hBitmap[2] = (HBITMAP)LoadImage(NULL, "char.bmp", IMAGE_BITMAP, 0, 0
			, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitmap[2]);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			BitBlt(g_MemDC[0], 0, 0, 1024, 768, g_MemDC[1], 0, 0, SRCCOPY);
			TransparentBlt(g_MemDC[0], x, y, 240, 192, g_MemDC[2], 0, 0, 240, 192, RGB(255, 0, 255));

			BitBlt(hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
		}

		POINT pt;
		pt.x;
		pt.y;

		RECT rc;//카드 렉트
		
		if (PtInRect(&rc, pt))
		{

		}

		SetRect(&rc, 0, 0, 10, 10);

		RECT rcTemp, rc1, rc2;
		if (IntersectRect(&rcTemp, &rc1, &rc2))
		{

		}

		
		return 0;
	case WM_TIMER:
	{
		static bool bLeft = false;

		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (bLeft == false)
			{
				//KeyDown
			}

			bLeft = true;
			x -= 10;
		}
		else
		{
			if (bLeft == true)
			{
				//KeyUp
			}
			bLeft = false;
		}

		if (GetKeyState(VK_RIGHT) & 0x8000)
			x += 10;
		if (GetKeyState(VK_UP) & 0x8000)
			y -= 10;
		if (GetKeyState(VK_DOWN) & 0x8000)
			y += 10;

		if (m_eState == PLAYER_STATE_JUMP)
		{
			m_dwJumpCount++;

			x = m_ptJumpPos.x - cosf(0.02f * m_dwJumpCount * PI) * 100;
			y = m_ptJumpPos.y - sinf(0.02f * m_dwJumpCount * PI) * 200;

			if (m_dwJumpCount >= 50)
				m_eState = PLAYER_STATE_WAIT;
		}
		else if (GetKeyState(VK_SPACE) & 0x8000)
		{
			m_eState = PLAYER_STATE_JUMP;
			m_ptJumpPos.x = x + 100;
			m_ptJumpPos.y = y;
			m_dwJumpCount = 0;
		}

		InvalidateRect(hWnd, NULL, false);
	}
		
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		return 0;
	
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}