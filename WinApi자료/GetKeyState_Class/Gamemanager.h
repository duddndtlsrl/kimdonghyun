#pragma once
#include<Windows.h>
#include"Bitmap.h"
class Gamemanager
{
private:
	static Gamemanager* m_pThis;
	Bitmap* m_btPlayer;
	Bitmap* m_btBack;

	int posX = 0;
	int posY = 0;

public:
	static Gamemanager* GetInstans()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new Gamemanager;
		}
		return m_pThis;
	}
	Gamemanager();

	void Init(HWND hWnd);
	void Draw(HDC hdc);
	void KeyboardInput();
	void Release();
	
	~Gamemanager();
};

