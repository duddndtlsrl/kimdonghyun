#include "bitmap.h"

void bitmap::init(HINSTANCE hinstance, HDC hdc, char * ch)
{
	mem_dc = CreateCompatibleDC(hdc);
	mem_bit = (HBITMAP)LoadImage(NULL, ch, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	old_bit = (HBITMAP)SelectObject(mem_dc, mem_bit);

	BITMAP bmp_info;
	GetObject(mem_bit, sizeof(bmp_info), &bmp_info);
	mem_size.cx = (int)bmp_info.bmWidth;
	mem_size.cy = (int)bmp_info.bmHeight;
}

void bitmap::draw(HDC hdc, int x, int y)
{
	BitBlt(hdc, x*mem_size.cx, y*mem_size.cx, mem_size.cx, mem_size.cy, mem_dc, 0, 0, SRCCOPY);
}

void bitmap::release()
{
	SelectObject(mem_dc, old_bit);
	DeleteObject(mem_bit);
	DeleteObject(mem_dc);
}

bitmap::bitmap()
{
}


bitmap::~bitmap()
{
}
