#include "GameManager.h"
#include "Macro.h"
#include "ResManager.h"
#include "Card.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	m_eGameState = GAME_STATE_WAIT;
	m_pSelectOne = NULL;
	m_pSelectTwo = NULL;
	m_dwCount = 0;
}


GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	m_hWnd = hWnd;

	SetTimer(m_hWnd, 1, 100, NULL);
	srand(GetTickCount());
	m_pResManager = new ResManager();
	m_pResManager->Init(hdc, hInst);

	int Arr[20];

	for (int i = 0; i < 20; i++)
	{
		Arr[i] = i % 10;
	}

	for (int i = 0; i < 100; i++)
	{
		int randA = rand() % 20;
		int randB = rand() % 20;

		int temp = Arr[randA];
		Arr[randA] = Arr[randB];
		Arr[randB] = temp;
	}

	for (int i = 0; i < 20; i++)
	{
		Card* pNew = new Card();
		pNew->Init(m_pResManager->GetBitMap(Arr[i]), m_pResManager->GetBitMap(RES_TYPE_BACK),
			Arr[i], i % 10 * CARD_WIDTH + i % 10 * 10  , i / 10 * CARD_HEIGHT + i / 10 * 10);
		m_vecCard.push_back(pNew);
	}
}

void GameManager::Update()
{
	if (m_eGameState != GAME_STATE_SHOW)
		return;

	m_dwCount++;

	if (m_dwCount >= 10)
	{
		m_dwCount = 0;
		m_pSelectOne->SetClose();
		m_pSelectTwo->SetClose();
		m_pSelectOne = NULL;
		m_pSelectTwo = NULL;
		m_eGameState = GAME_STATE_WAIT;
		InvalidateRect(m_hWnd, NULL, true);
	}
}

void GameManager::OnLBTClick(int x, int y)
{
	if (m_eGameState == GAME_STATE_SHOW)
		return;

	for (auto iter = m_vecCard.begin(); iter != m_vecCard.end(); iter++)
	{
		if ((*iter)->OnLBTClick(x, y))
		{
			if (m_eGameState == GAME_STATE_WAIT)
			{
				m_pSelectOne = (*iter);
				m_eGameState = GAME_STATE_SELECT;
			}
			else if (m_eGameState == GAME_STATE_SELECT)
			{
				m_pSelectTwo = (*iter);
				if (m_pSelectOne->GetIndex() == m_pSelectTwo->GetIndex())
				{
					m_pSelectOne = NULL;
					m_pSelectTwo = NULL;
					m_eGameState = GAME_STATE_WAIT;
				}
				else
					m_eGameState = GAME_STATE_SHOW;
			}

			InvalidateRect(m_hWnd, NULL, true);
		}
	}
}

void GameManager::Draw(HDC hdc)
{
	for (auto iter = m_vecCard.begin(); iter != m_vecCard.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void GameManager::Release()
{
	KillTimer(m_hWnd, 1);

	for (auto iter = m_vecCard.begin(); iter != m_vecCard.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}

	SAFE_DELETE(m_pResManager);
	SAFE_DELETE(m_pThis);
}
