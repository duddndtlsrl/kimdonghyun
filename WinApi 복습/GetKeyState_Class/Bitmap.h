#pragma once
#include<Windows.h>
class Bitmap
{
private:
	HDC		MemDC;
	HBITMAP	m_pMyBitMap;
	HBITMAP	m_pOldBitMap;
	SIZE	m_size;
public:
	Bitmap();

	void Init(HDC hdc, const char* szFileName, bool back = false);
	void Draw(HDC hdc, HDC back_dc, int x, int y, int dir=0, int order=0, bool bTransparent = false);
	HDC get_dc();

	~Bitmap();
};

