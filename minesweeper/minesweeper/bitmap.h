#pragma once
#include <Windows.h>
class bitmap
{
private:
	HDC mem_dc;
	HBITMAP mem_bit;
	HBITMAP old_bit;

	SIZE mem_size;

public:
	void init(HINSTANCE hinstance, HDC hdc, char* ch);
	void draw(HDC hdc, int x, int y);
	void release();
	bitmap();
	~bitmap();
};

