#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

enum GAME_STATE
{
	GAME_STATE_WAIT,
	GAME_STATE_SELECT,
	GAME_STATE_SHOW,
};

class Card;
class ResManager;
class GameManager
{
private:
	static GameManager* m_pThis;
	GameManager();

	HWND				m_hWnd;
	ResManager*			m_pResManager;
	vector<Card*>		m_vecCard;
	GAME_STATE			m_eGameState;
	Card*				m_pSelectOne;
	Card*				m_pSelectTwo;
	DWORD				m_dwCount;
public:
	static GameManager* GetInstance()
	{
		if (m_pThis == NULL)
			m_pThis = new GameManager();

		return m_pThis;
	}

	void Init(HWND hWnd, HDC hdc, HINSTANCE hInst);
	void Update();
	void OnLBTClick(int x, int y);
	void Draw(HDC hdc);
	void Release();

	~GameManager();
};

