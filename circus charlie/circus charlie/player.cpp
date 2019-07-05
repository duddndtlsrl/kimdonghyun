#include "player.h"
#include "bitmap.h"
#include "game_manager.h"

void player::init(bitmap* bit, int i)
{
	play[i] = bit;
}

void player ::set_pos(float count, float x, float y)
{
	
	if (jump)
	{
		if (pos_x - count < 0)
		{
			pos_x = count;
			pos_y = y;
		}
		else 
		{
			pos_x = x;
			pos_y = y;
		}
	}
	else
	{
		if (pos_x - count < 0)
		{
			pos_x = count;
			pos_y += y;
		}
		else 
		{
			pos_x += x;
			pos_y += y;
		}
	}

	move_rc();
}

void player::draw(HDC back_dc)
{
	if (jump)
		play[PLAYER_JUMP]->draw(back_dc, pos_x, pos_y);
	else if (is_dead)
		play[PLAYER_DIE]->draw(back_dc, pos_x, pos_y);
	else
	{
		if (run)
			play[PLAYER_RUN]->draw(back_dc, pos_x, pos_y);
		else 
			play[PLAYER_RUN1]->draw(back_dc, pos_x, pos_y);
	}
}

void player::move_rc()
{
	player_rc.left = pos_x + PLAYER_WIDTH / 3;
	player_rc.top = pos_y;
	player_rc.right = pos_x + PLAYER_WIDTH * 2 / 3;
	player_rc.bottom = pos_y + PLAYER_HEIGHT;
}

void player::game_over()
{
	is_dead = true;
}

player::player()
{
	pos_x = 100;
	pos_y = MENU_HEIGHT+180;
	is_dead = false;
	jump = false;
	run = true;
	move_rc();
}


player::~player()
{
}
