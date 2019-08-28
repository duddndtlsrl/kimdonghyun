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
	m_btBackGr = new Bitmap;

	m_btPlayer->Init(hdc, "image.bmp");
	m_btBack->Init(hdc, "back.bmp");
	m_btBackGr->Init(hdc, "", true);
}

void Gamemanager::Draw(HDC hdc)
{
	m_btBack->Draw(hdc, m_btBackGr->get_dc(), 0, 0);
	m_btPlayer->Draw(hdc, m_btBackGr->get_dc(), posX, posY, cur_direction, cur_order,  true);
}

void Gamemanager::KeyboardInput()
{
	bool flag = false;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		posX -= 10;
		cur_direction = DIR_LEFT;
		flag = true;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		posX += 10;
		cur_direction = DIR_RIGHT;
		flag = true;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		posY -= 10;
		cur_direction = DIR_UP;
		flag = true;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		posY += 10;
		cur_direction = DIR_DOWN;
		flag = true;
	}

	if (flag)
	{
		if (cur_order == 3)
			cur_order = 0;
		else
			cur_order++;
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
