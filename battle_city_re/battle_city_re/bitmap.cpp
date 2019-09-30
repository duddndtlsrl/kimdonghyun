#include "bitmap.h"
#include "res_manager.h"

void bitmap::init(HDC hdc, char* ch, bool back_bit)
{
	mem_dc = CreateCompatibleDC(hdc);
	if (back_bit)
		my_bit = (HBITMAP)CreateCompatibleBitmap(hdc, 14 * BL_WIDTH, 13 * BL_HEIGHT);
	else
		my_bit = (HBITMAP)LoadImage(NULL, ch, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	old_bit = (HBITMAP)SelectObject(mem_dc, my_bit);

	BITMAP bmp_info;
	GetObject(my_bit, sizeof(bmp_info), &bmp_info);
	bit_size.cx = bmp_info.bmWidth;
	bit_size.cy = bmp_info.bmHeight;

	return;
}

void bitmap::draw(HDC hdc, float pos_x, float pos_y, bool back_bit, bool block, bool object)
{
	if (object)
	{
		TransparentBlt(hdc, pos_x, pos_y, bit_size.cx, bit_size.cy, mem_dc, 0, 0, bit_size.cx, bit_size.cy, RGB(255, 0, 255));
		return;
	}
	
	if (back_bit)
	{
		BitBlt(hdc, 0, 0, bit_size.cx, bit_size.cy, mem_dc, 0, 0, SRCCOPY );
	}
	else
	{
		if(block)
			TransparentBlt(hdc, BL_WIDTH*pos_x, BL_HEIGHT*pos_y, BL_WIDTH, BL_HEIGHT, mem_dc, 0, 0, bit_size.cx, bit_size.cy, RGB(255, 0, 255));
		else
			TransparentBlt(hdc, pos_x, pos_y, BL_WIDTH, BL_HEIGHT, mem_dc, 0, 0, bit_size.cx, bit_size.cy, RGB(255, 0, 255));
	}

	

	return;
}

HDC bitmap::get_dc()
{
	return mem_dc;
}

bitmap::bitmap()
{
}


bitmap::~bitmap()
{
	SelectObject(mem_dc, old_bit);
	DeleteObject(my_bit);
	DeleteObject(old_bit);
	DeleteObject(mem_dc);
}
