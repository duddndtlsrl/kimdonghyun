#include "enemy_move.h"

enemy_move::enemy_move(int x)
{
	pos_x = x * (WINDOW_WIDTH + ENEMY_WIDTH) + WINDOW_WIDTH;
	pos_y = MENU_HEIGHT+67;
	is_blink = false;
}


enemy_move::~enemy_move()
{
}
