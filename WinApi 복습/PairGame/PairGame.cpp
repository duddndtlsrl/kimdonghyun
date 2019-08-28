#include <windows.h>
#include "resource.h"

void Init();
void Release();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";
HWND g_hWnd;

#define IMAGE_WIDTH 145
#define IMAGE_HEIGHT 235

enum IMAGE
{
	IMAGE_00,
	IMAGE_01,
	IMAGE_02,
	IMAGE_03,
	IMAGE_04,
	IMAGE_05,
	IMAGE_06,
	IMAGE_07,
	IMAGE_08,
	IMAGE_09,
	IMAGE_BACK,
	IMAGE_END
};

HDC			g_hMemDC;
HBITMAP		g_hBitMap[IMAGE_END];
HBITMAP		g_hOldBitMap;

enum GAME_STATE
{
	GAME_STATE_NONE,
	GAME_STATE_ONE,
	GAME_STATE_TWO
};

struct OPEN_STATE
{
	GAME_STATE		state;
	int				first;
	int				second;
	int				showCount;
};

OPEN_STATE g_GameState;

class Card
{
public:
	bool				m_bOpend;
	int					m_nType;
	RECT				m_rcRect;

	Card()
	{
		m_bOpend = false;
		m_nType = 0;
		SetRect(&m_rcRect, 0, 0, 0, 0);
	}

	void				Draw(HDC hdc)
	{
		HBITMAP old;

		if (m_bOpend == true)
		{
			old = (HBITMAP)SelectObject(g_hMemDC, g_hBitMap[m_nType]);
			BitBlt(hdc, m_rcRect.left , m_rcRect.top , IMAGE_WIDTH, IMAGE_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
		}
		else
		{
			old = (HBITMAP)SelectObject(g_hMemDC, g_hBitMap[IMAGE_BACK]);
			BitBlt(hdc, m_rcRect.left, m_rcRect.top, IMAGE_WIDTH, IMAGE_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
		}
			

		SelectObject(g_hMemDC, old);
	}
};

Card		g_Card[20];

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
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	g_hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(g_hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 0, 100, NULL);
		Init();
		return 0;
	case  WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			for (int i = 0; i < 20; i++)
			{
				if (g_Card[i].m_bOpend)
					continue;

				if (PtInRect(&g_Card[i].m_rcRect, pt))
				{
					if (g_GameState.state == GAME_STATE_NONE)
					{
						g_GameState.first = i;
						g_Card[i].m_bOpend = true;
						g_GameState.state = GAME_STATE_ONE;
					}
					else if (g_GameState.state == GAME_STATE_ONE)
					{
						g_GameState.second = i;
						g_Card[i].m_bOpend = true;
						g_GameState.state = GAME_STATE_TWO;
						g_GameState.showCount = 0;
					}
					
					InvalidateRect(hWnd, NULL, true);
				}
			}
		}
		return 0;
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 20; i++)
		{
			g_Card[i].Draw(hdc);
		}
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		if (g_GameState.state == GAME_STATE_TWO)
		{
			g_GameState.showCount++;
			if (g_GameState.showCount > 10)
			{
				if (g_Card[g_GameState.first].m_nType != g_Card[g_GameState.second].m_nType)
				{
					g_Card[g_GameState.first].m_bOpend = false;
					g_Card[g_GameState.second].m_bOpend = false;
				}

				g_GameState.state = GAME_STATE_NONE;
				g_GameState.first = 0;
				g_GameState.second = 0;
				g_GameState.showCount = 0;

				InvalidateRect(hWnd, NULL, true);
			}
		}
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		Release();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void Init()
{
	srand(GetTickCount());

	HDC hdc = GetDC(g_hWnd);
	g_hMemDC = CreateCompatibleDC(hdc);

	for (int i = 0; i < IMAGE_END; i++)
	{
		g_hBitMap[i] =  LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	g_hOldBitMap = (HBITMAP)SelectObject(g_hMemDC, g_hBitMap[0]);

	ReleaseDC(g_hWnd, hdc);

	int arry[20] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };

	for (int i = 0; i < 100; i++)
	{
		int randA = rand() % 20;
		int randB = rand() % 20;

		int nTemp = arry[randA];
		arry[randA] = arry[randB];
		arry[randB] = nTemp;
	}

	for (int i = 0; i < 20; i++)
	{
		g_Card[i].m_nType = arry[i];
		g_Card[i].m_rcRect.left = (i % 10) * (IMAGE_WIDTH + 10);
		g_Card[i].m_rcRect.right = g_Card[i].m_rcRect.left + IMAGE_WIDTH;
		g_Card[i].m_rcRect.top = (i / 10) * (IMAGE_HEIGHT + 10);
		g_Card[i].m_rcRect.bottom = g_Card[i].m_rcRect.top + IMAGE_HEIGHT;
	}
}

void Release()
{
	SelectObject(g_hMemDC , g_hOldBitMap);
	DeleteDC(g_hMemDC);
}