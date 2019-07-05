#include "bitmap.h"


void bitmap::init(HDC hdc, char* ch, int pos)
{
	mem_dc = CreateCompatibleDC(hdc);
	mem_bit = (HBITMAP)LoadImage(NULL, ch, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	old_bit = (HBITMAP)SelectObject(mem_dc, mem_bit);
	my_pos = pos;

	BITMAP bmp_info;
	GetObject(mem_bit, sizeof(bmp_info), &bmp_info);
	mem_size.cx = (int)bmp_info.bmWidth;
	mem_size.cy = (int)bmp_info.bmHeight;
	
}

void bitmap::draw(HDC back_dc, int i)
{
	TransparentBlt(back_dc, mem_size.cx*i, my_pos, mem_size.cx, mem_size.cy, mem_dc, 0, 0, mem_size.cx, mem_size.cy, RGB(255, 0, 255));
}

void bitmap::draw(HDC back_dc, float pos_x, float pos_y)
{
	TransparentBlt(back_dc, pos_x, pos_y, mem_size.cx, mem_size.cy, mem_dc, 0, 0, mem_size.cx, mem_size.cy, RGB(255, 0, 255));
}

bitmap::bitmap()
{
}

bitmap::~bitmap()
{
}
