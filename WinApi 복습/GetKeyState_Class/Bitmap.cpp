#include "Bitmap.h"

Bitmap::Bitmap()
{
}

void Bitmap::Init(HDC hdc, const char* szFileName, bool back)
{
	MemDC = CreateCompatibleDC(hdc);
	if (back)
	{
		m_pMyBitMap = CreateCompatibleBitmap(hdc, 720, 1080);
		m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);
	}
	else 
	{
		m_pMyBitMap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);

		BITMAP Bit_Info;

		GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
		m_size.cx = Bit_Info.bmWidth;
		m_size.cy = Bit_Info.bmHeight;
	}
}

void Bitmap::Draw(HDC hdc, HDC back_dc, int x, int y, int dir, int order, bool bTransparent)
{

		TransparentBlt(back_dc, x, y, m_size.cx / 4, m_size.cy / 4, MemDC, m_size.cx/4*order, m_size.cy/4*dir, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
		StretchBlt(back_dc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
		BitBlt(hdc, 0, 0, 720, 1080, back_dc, 0, 0, SRCCOPY);

}

HDC Bitmap::get_dc()
{
	return MemDC;
}

Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_pOldBitMap);
	DeleteObject(m_pMyBitMap);
	DeleteDC(MemDC);
}
