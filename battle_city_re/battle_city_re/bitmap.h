#pragma once
#include<Windows.h>
class bitmap
{
private:
	HDC mem_dc;
	HBITMAP my_bit;
	HBITMAP old_bit;
	SIZE bit_size;
public:
	void init(HDC hdc, char* ch, bool back_bit=false);
	void draw(HDC hdc, float pos_x, float pos_y, bool back_bit = false, bool block=false);
	HDC get_dc();
	bitmap();
	~bitmap();
};

