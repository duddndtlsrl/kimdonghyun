#pragma once
#include<Windows.h>

class bitmap
{
private:
	HDC mem_dc;

	HBITMAP mem_bit;
	HBITMAP old_bit;
	int my_pos;

	SIZE mem_size;

public:
	void init(HDC hdc, char* ch, int pos);
	void draw(HDC back_dc, int i);
	void draw(HDC back_dc, float pos_x, float pos_y);
	bitmap();
	~bitmap();
};

