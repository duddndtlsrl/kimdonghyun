#include "res_manager.h"
#include "bitmap.h"

void res_manager::init(HDC hdc, HINSTANCE hinst)
{
	char* ch = new char[11];
	for (int i = BACK_GROUND_UP; i != BACK_GROUND_END; i++)
	{
		back_gr[i] = new bitmap();
		wsprintf(ch, "back_%d.bmp", i);
		back_gr[i]->init(hdc, hinst, ch);
	}
	char* ch1 = new char[13];
	for (int i = PLAYER_RUN; i != PLAYER_END; i++)
	{
		player[i] = new bitmap();
		wsprintf(ch1, "player_%d.bmp", i);
		player[i]->init(hdc, hinst, ch1);
	}
	delete[] ch;
	delete[] ch1;
}

res_manager::res_manager()
{
}


res_manager::~res_manager()
{
}
