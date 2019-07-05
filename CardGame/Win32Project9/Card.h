#pragma once
#include <Windows.h>

#define CARD_WIDTH		145
#define CARD_HEIGHT		235

class BitMap;
class Card
{
private:
	BitMap*		m_pBitMap;
	BitMap*		m_pBackBitMap;
	int			m_iIndex;
	int			m_iX;
	int			m_iY;
	bool		m_bOpen;
public:
	void		Init(BitMap* pBitMap, BitMap* pBackBitMap, int index, int x, int y);
	bool		OnLBTClick(int x, int y);
	void		Draw(HDC hdc);
	void		Release();
	inline int	GetIndex()
	{
		return m_iIndex;
	}
	inline void SetClose()
	{
		m_bOpen = false;
	}
	Card();
	~Card();
};

