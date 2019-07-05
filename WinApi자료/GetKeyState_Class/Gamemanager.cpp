#include "Gamemanager.h"


Gamemanager* Gamemanager::m_pThis = NULL;

Gamemanager::Gamemanager()
{
}
void Gamemanager::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	m_btPlayer = new Bitmap;
	m_btBack = new Bitmap;

	m_btPlayer->Init(hdc, "image.bmp");
	m_btBack->Init(hdc, "back.bmp");
}

void Gamemanager::Draw(HDC hdc)
{
	m_btBack->Draw(hdc, 0, 0);
	m_btPlayer->Draw(hdc, posX, posY, true);
}

void Gamemanager::KeyboardInput()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		posX -= 10;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		posX += 10;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		posY -= 10;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		posY += 10;
	}
}

void Gamemanager::Release()
{
	delete(m_pThis);
}

Gamemanager::~Gamemanager()
{
	delete(m_btPlayer);
	delete(m_btBack);
}
