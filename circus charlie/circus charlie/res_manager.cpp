#include "res_manager.h"
#include "bitmap.h"
#include "player.h"
#include "enemy.h"
#include "cash.h"
#include "game_manager.h"

void res_manager::init(HDC hdc)
{
	back_dc = CreateCompatibleDC(hdc);
	char* ch = new char[11];
	for (int i = BACK_GROUND_UP; i != BACK_GROUND_END; i++)
	{
		back_gr[i] = new bitmap();
		wsprintf(ch, "back_%d.bmp", i);
		if (i == BACK_GROUND_DOWN)
			back_gr[i]->init(hdc, ch, MENU_HEIGHT+67);
		else
			back_gr[i]->init(hdc, ch, MENU_HEIGHT + 0);
	}
	char* ch1 = new char[13];
	for (int i = PLAYER_RUN; i != PLAYER_END; i++)
	{
		players[i] = new bitmap();
		wsprintf(ch1, "player_%d.bmp", i);
		players[i]->init(hdc, ch1, 0);
	}
	char* ch2 = new char[12];
	for (int i = ENEMY_A_NORMAL; i != ENEMY_END; i++)
	{
		enemy_bit[i] = new bitmap();
		wsprintf(ch2, "enemy_%d.bmp", i);
		enemy_bit[i]->init(hdc, ch2, 0);
	}
	char* ch3 = new char[15];
	for (int i = RESOURCE_METER; i != RESOURCE_END; i++)
	{
		resource[i] = new bitmap();
		wsprintf(ch3, "resource_%d.bmp", i);
		resource[i]->init(hdc, ch3, 0);
	}

	delete[] ch;
	delete[] ch1;
	delete[] ch2;
	delete[] ch3;

}

void res_manager::draw(HDC hdc, int score, int bonus, float count, vector<enemy*>* enemies, player* p_player, cash* p_cash)
{
	back_bit = CreateCompatibleBitmap(hdc, 20000, 720);
	old_bit = (HBITMAP)SelectObject(back_dc, back_bit);
	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH old_brush = (HBRUSH)SelectObject(back_dc, brush);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN pen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HPEN old_pen = (HPEN)SelectObject(back_dc, pen1);
	Rectangle(back_dc, count+30, 2, count + WINDOW_WIDTH - 30, 40);
	SelectObject(back_dc, pen);
	Rectangle(back_dc, count + 32, 4, count + WINDOW_WIDTH - 32, 38);
	
	SetBkMode(back_dc, TRANSPARENT);
	SetTextColor(back_dc, RGB(255, 255, 255));
	char* ch1 = new char[30];
	wsprintf(ch1, "SCORE: %d", score);
	TextOut(back_dc, count + 32, 4, ch1, lstrlen(ch1));
	wsprintf(ch1, "BONUS: %d", bonus);
	TextOut(back_dc, count + 270, 4, ch1, lstrlen(ch1));

	SelectObject(back_dc, old_pen);
	SelectObject(back_dc, old_brush);
	DeleteObject(brush);
	DeleteObject(pen);
	DeleteObject(pen1);

	for (int i = 0; 66*i < WINDOW_WIDTH*11; i++)
	{
		if(i%6==0)
			back_gr[BACK_GROUND_UP]->draw(back_dc, i);
		else
			back_gr[BACK_GROUND_UP1]->draw(back_dc, i);
		
		back_gr[BACK_GROUND_DOWN]->draw(back_dc, i);
	}

	char* ch = new char[3];
	SetTextColor(back_dc, RGB(255, 255, 0));
	for (int i = 0; i < 11; i++)
	{
		resource[RESOURCE_METER]->draw(back_dc, i*WINDOW_WIDTH, MENU_HEIGHT+250);
		sprintf(ch, "%d", 100 - i * 10);
		TextOut(back_dc, i*WINDOW_WIDTH + 20, MENU_HEIGHT + 256, ch, lstrlen(ch));
	}
		
	for (auto iter = enemies->begin(); iter != enemies->end(); iter++)
			(*iter)->draw(back_dc);
	p_cash->draw(back_dc);
	p_player->draw(back_dc);
	BitBlt(hdc, 0, 0, WINDOW_WIDTH, 720, back_dc, count, 0, SRCCOPY);

	DeleteObject(back_bit);
	
}

res_manager::res_manager()
{
}


res_manager::~res_manager()
{
}
