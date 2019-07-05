#include "game_manager.h"
#include "res_manager.h"
#include "player.h"
#include "bitmap.h"

game_manager* game_manager::instance = nullptr;

game_manager::game_manager()
{
}


void game_manager::init(HDC hdc, HINSTANCE hinst)
{
	g_hdc = hdc;
	back_dc = CreateCompatibleDC(g_hdc);
	back_bit = CreateCompatibleBitmap(g_hdc, 1080, 720);
	SelectObject(back_dc, back_bit);

	res_manage = new res_manager();
	res_manage->init(g_hdc, hinst);
	p_player = new player();
	for (int i = PLAYER_RUN; i < PLAYER_END; i++)
		p_player->init(res_manage->get_player(i), i);

}

void game_manager::draw()
{
	(res_manage->get_back(BACK_GROUND_UP))->draw(g_hdc, 1, 1, 1, 0);
}
game_manager::~game_manager()
{
}
