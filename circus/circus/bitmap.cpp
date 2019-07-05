#include "bitmap.h"


void bitmap::init(HDC hdc, HINSTANCE hinst, char* ch)
{
	back_dc = CreateCompatibleDC(hdc);
	mem_dc = CreateCompatibleDC(back_dc);
	back_bit = CreateCompatibleBitmap(back_dc, 1080, 720);
	old_bit = (HBITMAP)SelectObject(back_dc, back_bit);
	mem_bit = (HBITMAP)LoadImage(hinst, ch, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	SelectObject(mem_dc, mem_bit);

	BITMAP bmp_info;
	GetObject(mem_bit, sizeof(bmp_info), &bmp_info);
	mem_size.cx = (int)bmp_info.bmWidth;
	mem_size.cy = (int)bmp_info.bmHeight;
	
}

void bitmap::draw(HDC hdc, int i, int pos_x, int pos_y, int my_pos)
{
	TransparentBlt(back_dc, mem_size.cx*i, my_pos + mem_size.cy*i, mem_size.cx, mem_size.cy, mem_dc, 0, 0, mem_size.cx, mem_size.cy, RGB(255, 0, 255));
	BitBlt(hdc, 0, 0, 1080, 720, back_dc, 0, 0, SRCCOPY);
}

bitmap::bitmap()
{
}

bitmap::~bitmap()
{
}
