#include <Windows.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR szClassName = "≈ ≈©∏ ≈¯";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	int			nWidth, nHeight;//¿©µµøÏ ≈©±‚ 
	nWidth = 1024 + GetSystemMetrics(SM_CXFRAME) * 2;
	nHeight = 768 + GetSystemMetrics(SM_CYFRAME) * 2 +
		GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);

	hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, 0, 0,
		nWidth, nHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

#define WIDTH 33
#define HEIGHT 25

int g_map[13][13];
int cur_select = 0;

HDC mem_dc[14];
HBITMAP mem_bit[14];
HBITMAP old_bit[14];




LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_CREATE:
		{
		CreateWindow("button", "BRICK_W", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 800, 0, 100, 30, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow("button", "BRICK_U", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 20, 100, 30, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow("button", "BRICK_D", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 40, 100, 30, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow("button", "BRICK_L", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 60, 100, 30, hWnd, (HMENU)3, g_hInst, NULL);
		CreateWindow("button", "BRICK_R", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 80, 100, 30, hWnd, (HMENU)4, g_hInst, NULL);
		CreateWindow("button", "STONE_W", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 100, 100, 30, hWnd, (HMENU)5, g_hInst, NULL);
		CreateWindow("button", "STONE_U", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 120, 100, 30, hWnd, (HMENU)6, g_hInst, NULL);
		CreateWindow("button", "STONE_D", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 0, 100, 30, hWnd, (HMENU)7, g_hInst, NULL);
		CreateWindow("button", "STONE_L", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 20, 100, 30, hWnd, (HMENU)8, g_hInst, NULL);
		CreateWindow("button", "STONE_R", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 40, 100, 30, hWnd, (HMENU)9, g_hInst, NULL);
		CreateWindow("button", "ICE", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 60, 100, 30, hWnd, (HMENU)10, g_hInst, NULL);
		CreateWindow("button", "BUSH", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 80, 100, 30, hWnd, (HMENU)11, g_hInst, NULL);
		CreateWindow("button", "LAKE", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 100, 100, 30, hWnd, (HMENU)12, g_hInst, NULL);
		CreateWindow("button", "HQ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 120, 100, 30, hWnd, (HMENU)13, g_hInst, NULL);
		CreateWindow("button", "EMPTY", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 140, 100, 30, hWnd, (HMENU)15, g_hInst, NULL);

		CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 400, 100, 30, hWnd, (HMENU)100, g_hInst, NULL);
		CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 450, 100, 30, hWnd, (HMENU)101, g_hInst, NULL);

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				g_map[i][j] = 15;
			}
		}

		hdc = GetDC(hWnd);
		char* ch = new char[20];
		for (int i = 0; i < 14; i++)
		{
			if (i < 10)
				wsprintf(ch, "block0%d.bmp", i);
			else
				wsprintf(ch, "block%d.bmp", i);
			mem_dc[i] = CreateCompatibleDC(hdc);
			mem_bit[i] = (HBITMAP)LoadImage(NULL, ch, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);
			old_bit[i] = (HBITMAP)SelectObject(mem_dc[i], mem_bit[i]);
		}
		delete ch;
		ReleaseDC(hWnd, hdc);
		}
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					int num = g_map[i][j];
					if (num == 15)
						Rectangle(hdc, WIDTH*j, HEIGHT*i, WIDTH*(j + 1), HEIGHT*(i + 1));
					else
						TransparentBlt(hdc, WIDTH*j, HEIGHT*i, WIDTH, HEIGHT, mem_dc[num], 0, 0, WIDTH, HEIGHT, RGB(255, 0, 255));
				}
			}
			EndPaint(hWnd, &ps);
			return 0;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 15:	
				cur_select = LOWORD(wParam);
				break;
			case 100: //SAVE
			{
				OPENFILENAME OFN;
				char str[300];
				char lpstrFile[MAX_PATH] = "";
				char lpstrPath[MAX_PATH] = "";

				memset(&OFN, 0, sizeof(OPENFILENAME));
				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = hWnd;
				OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
				OFN.lpstrFile = lpstrFile;
				OFN.nMaxFile = 256;
				GetCurrentDirectory(MAX_PATH, lpstrPath);
				OFN.lpstrInitialDir = lpstrPath;
				if (GetSaveFileName(&OFN) == 0)
				{
					DWORD err = CommDlgExtendedError();
					break;
				}

				HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 13; j++)
					{
						DWORD writeB;
						WriteFile(hFile, &g_map[i][j], sizeof(int), &writeB, NULL);
					}
				}
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, true);
			}
			break;
			case 101://load
			{
				OPENFILENAME OFN;
				char str[300];
				char lpstrFile[MAX_PATH] = "";
				char lpstrPath[MAX_PATH] = "";

				memset(&OFN, 0, sizeof(OPENFILENAME));
				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = hWnd;
				OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
				OFN.lpstrFile = lpstrFile;
				OFN.nMaxFile = 256;
				GetCurrentDirectory(MAX_PATH, lpstrPath);
				OFN.lpstrInitialDir = lpstrPath;
				if (GetSaveFileName(&OFN) == 0)
				{
					DWORD err = CommDlgExtendedError();
					break;
				}

				HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 13; j++)
					{
						DWORD readB;
						ReadFile(hFile, &g_map[i][j], sizeof(int), &readB, NULL);
					}
				}
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
			}
			return 0; 
		}

		case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if ((pt.x < WIDTH * 13 && pt.x > 0) && (pt.y < HEIGHT * 13 && pt.y > 0))
			{
				g_map[pt.y / HEIGHT][pt.x / WIDTH] = cur_select;
				InvalidateRect(hWnd, NULL, false);
			}
		}
		return 0;
		case WM_DESTROY:
			for (int i = 0; i < 14; i++)
			{
				SelectObject(mem_dc[i], old_bit[i]);
				DeleteObject(mem_bit[i]);
				DeleteObject(old_bit[i]);
			}
			PostQuitMessage(0);
			return 0;
	
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}