#include "Card.h"
#include "BitMap.h"

Card::Card()
{
	m_bOpen = false;
}


Card::~Card()
{
}

void Card::Init(BitMap* pBitMap, BitMap* pBackBitMap, int index, int x, int y)
{
	m_pBitMap = pBitMap;
	m_pBackBitMap = pBackBitMap;
	m_iIndex = index;
	m_iX = x;
	m_iY = y;
}

bool Card::OnLBTClick(int x, int y)
{
	if (m_bOpen)
		return false;

	RECT rc = { m_iX , m_iY , m_iX + CARD_WIDTH , m_iY + CARD_HEIGHT };
	POINT pt = { x , y };
	if (PtInRect(&rc, pt))
	{
		m_bOpen = true;
		return true;
	}

	return false;
}

void Card::Draw(HDC hdc)
{
	if (m_bOpen)
		m_pBitMap->Draw(hdc, m_iX, m_iY);
	else
		m_pBackBitMap->Draw(hdc, m_iX, m_iY);
}

void Card::Release()
{

}
