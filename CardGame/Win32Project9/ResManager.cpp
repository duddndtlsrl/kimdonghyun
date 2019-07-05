#include "ResManager.h"
#include "BitMap.h"
#include "resource.h"
#include "Macro.h"

ResManager::ResManager()
{
}


ResManager::~ResManager()
{
}

void ResManager::Init(HDC hdc, HINSTANCE hInst)
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		m_pBitMap[i] = new BitMap();
		m_pBitMap[i]->Init(hdc, hInst, IDB_BITMAP1 + i);
	}
}

BitMap* ResManager::GetBitMap(int id)
{
	return m_pBitMap[id];
}

void ResManager::Release()
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		SAFE_DELETE(m_pBitMap[i]);
	}
}
