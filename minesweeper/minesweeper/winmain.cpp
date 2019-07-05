#include <windows.h>
#include "game_manager.h"
#include "resource.h"

BOOL CALLBACK SettingDlgProc(HWND hdlg, UINT iMassage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR IpszClass = TEXT("minesweeper");
HWND hWnd;
MSG Message;
WNDCLASS WndClass;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
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
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (iMassage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CONFIG_DIFFICULTY:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SettingDlgProc);
			
			break;
		}
	
	case WM_CREATE:
		hdc = GetDC(hWnd);
		game_manager::get_instance()->init(hWnd, hdc, g_hInst);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		game_manager::get_instance()->draw(hdc);
		EndPaint(hWnd, &ps);
		if (game_manager::get_instance()->game_end())
		{
			game_manager::get_instance()->release();
			SendMessage(hWnd, WM_CREATE, 0, 0);
		}
		return 0;
	case WM_LBUTTONUP:
		game_manager::get_instance()->left_click(LOWORD(IParam), HIWORD(IParam));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_RBUTTONUP:
		game_manager::get_instance()->right_click(LOWORD(IParam), HIWORD(IParam));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		game_manager::get_instance()->release();		
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMassage, wParam, IParam));
}

HWND hradio;

BOOL CALLBACK SettingDlgProc(HWND hdlg, UINT iMassage, WPARAM wParam, LPARAM lParam)
{
	switch (iMassage)
	{
	case WM_INITDIALOG:
		hradio = GetDlgItem(hdlg, IDC_RADIO1);
		SendMessage(hradio, BM_SETCHECK, BST_CHECKED, 0);
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			if (IsDlgButtonChecked(hdlg, IDC_RADIO1) == BST_CHECKED)
			{
				MessageBox(hWnd, "초급", "난이도", MB_OK);
				game_manager::get_instance()->cell_release(9, 10);
			}
			if (IsDlgButtonChecked(hdlg, IDC_RADIO2) == BST_CHECKED)
			{
				MessageBox(hWnd, "중급", "난이도", MB_OK);
				game_manager::get_instance()->cell_release(18, 20);
			}
			if (IsDlgButtonChecked(hdlg, IDC_RADIO3) == BST_CHECKED)
			{
				MessageBox(hWnd, "고급", "난이도", MB_OK);
				game_manager::get_instance()->cell_release(32, 30);
			}
			game_manager::get_instance()->make_cell();
			EndDialog(hdlg, 0);
		}
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}