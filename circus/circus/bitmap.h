#pragma once
#include<Windows.h>

class bitmap
{
private:
	HDC mem_dc;
	HDC back_dc;

	HBITMAP back_bit;
	HBITMAP mem_bit;
	HBITMAP old_bit;

	SIZE mem_size;

public:
	void init(HDC hdc, HINSTANCE hinst, char* ch);
	void draw(HDC hdc, int i, int pos_x, int pos_y, int my_pos);
	bitmap();
	~bitmap();
};

