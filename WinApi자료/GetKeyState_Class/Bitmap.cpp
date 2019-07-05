#include "Bitmap.h"

Bitmap::Bitmap()
{
}

void Bitmap::Init(HDC hdc, const char* szFileName)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pMyBitMap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);

	BITMAP Bit_Info;

	GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}

void Bitmap::Draw(HDC hdc, int x, int y, bool bTransparent)
{
	if (bTransparent)
	{
		TransparentBlt(hdc, x, y, m_size.cx / 4, m_size.cy / 4, MemDC, 0, 0, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	}
	else
	{
		StretchBlt(hdc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	}
}

Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_pOldBitMap);
	DeleteObject(m_pMyBitMap);
	DeleteDC(MemDC);
}
