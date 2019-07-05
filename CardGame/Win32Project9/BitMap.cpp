#include "BitMap.h"



BitMap::BitMap()
{
}


BitMap::~BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst , int id)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(id));
	m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

	BITMAP bmp_info;
	GetObject(m_hBitMap, sizeof(bmp_info), &bmp_info);
	m_size.cx = (int)bmp_info.bmWidth;
	m_size.cy = (int)bmp_info.bmHeight;
}

void BitMap::Draw(HDC hdc , int x , int y)
{
	BitBlt(hdc, x, y, m_size.cx , m_size.cy , m_hMemDC , 0 , 0 , SRCCOPY);
}

void BitMap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
