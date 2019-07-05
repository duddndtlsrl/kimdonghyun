#include <Windows.h>

#define BL_WIDTH 30
#define BL_HEIGHT 20

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR IpszClass = TEXT("maptool");

int map[12][12];
int cur_select = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	int nWidth = 650 + GetSystemMetrics(SM_CXFRAME) * 2;
	int nHeight = 384 + GetSystemMetrics(SM_CYFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, nWidth, nHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return(int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMassage, WPARAM wParam, LPARAM IParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMassage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			cur_select = 0;
			break;
		case 1:
			cur_select = 1;
			break;
		case 2:
			cur_select = 2;
			break;
		case 3:
		{
			OPENFILENAME OFN;
			char str[300];
			char lpstrFile[MAX_PATH] = "";
			char lpstrPath[MAX_PATH] = "";

			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = "Every File(*.*)\0*.*\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			GetCurrentDirectory(MAX_PATH, lpstrPath);
			OFN.lpstrInitialDir = lpstrPath;

			if (GetSaveFileName(&OFN) == 0)
			{
				DWORD err = CommDlgExtendedError();
				break;
			}
			else
			{
				HANDLE hfile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 12; j++)
					{
						DWORD writeB;

						WriteFile(hfile, &map[i][j], sizeof(int), &writeB, NULL);
					}
				}
				CloseHandle(hfile);
			}
		}
		break;
		case 4:
		{
			OPENFILENAME OFN;
			char str[300];
			char lpstrFile[MAX_PATH] = "";
			char lpstrPath[MAX_PATH] = "";

			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = "Every File(*.*)\0*.*\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			GetCurrentDirectory(MAX_PATH, lpstrPath);
			OFN.lpstrInitialDir = lpstrPath;

			if (GetOpenFileName(&OFN) == 0)
			{
				DWORD err = CommDlgExtendedError();
				break;
			}
			else
			{
				HANDLE hfile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 12; j++)
					{
						DWORD writeB;

						ReadFile(hfile, &map[i][j], sizeof(int), &writeB, NULL);
					}
				}
				CloseHandle(hfile);
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (map[i][j] == 0)
				{
					Rectangle(hdc, j*BL_WIDTH, i*BL_HEIGHT, (j + 1)*BL_WIDTH, (i + 1)*BL_HEIGHT);
				}
				else if (map[i][j] == 1)
				{
					Ellipse(hdc, j*BL_WIDTH, i*BL_HEIGHT, (j + 1)*BL_WIDTH, (i + 1)*BL_HEIGHT);
				}
				else
				{
					HBRUSH hblack = (HBRUSH)GetStockObject(BLACK_BRUSH);
					HBRUSH old = (HBRUSH)SelectObject(hdc, hblack);
					Ellipse(hdc, j*BL_WIDTH, i*BL_HEIGHT, (j + 1)*BL_WIDTH, (i + 1)*BL_HEIGHT);
					SelectObject(hdc, old);
					DeleteObject(hblack);
				}

			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CREATE:
		CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 500, 0, 100, 30, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 500, 40, 100, 30, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 500, 80, 100, 30, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow("button", "save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_GROUP, 500, 200, 100, 30, hWnd, (HMENU)3, g_hInst, NULL);
		CreateWindow("button", "load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_GROUP, 500, 250, 100, 30, hWnd, (HMENU)4, g_hInst, NULL);
		return 0;
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		pt.x = LOWORD(IParam);
		pt.y = HIWORD(IParam);

		if (pt.x < BL_WIDTH * 12 && pt.x>0 && pt.y < BL_HEIGHT * 12 && pt.y>0)
			map[pt.y / BL_HEIGHT][pt.x / BL_WIDTH] = cur_select;

		InvalidateRect(hWnd, NULL, TRUE);
			
	}
	return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMassage, wParam, IParam));
}