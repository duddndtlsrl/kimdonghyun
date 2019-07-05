#include "enemy.h"
#include "bitmap.h"

bool enemy::is_collide(RECT* rc_temp, RECT* rc_player, bool& score_flag)
{
	if (IntersectRect(rc_temp, &rc_score, rc_player))
		score_flag = true;
	
	if (IntersectRect(rc_temp, &rc_enemy, rc_player))
		return true;
	else
		return false;
}

void enemy::draw(HDC back_dc)
{
	if (is_blink)
		blink->draw(back_dc, pos_x, pos_y);
	else
		normal->draw(back_dc, pos_x, pos_y);
}

void enemy::init(bitmap* bit, bitmap* bit1, int y)
{
	normal = bit;
	blink = bit1;
	y_len = y;

	move_rc();
}

void enemy::move_rc()
{
	rc_enemy.left = pos_x + 20;
	rc_enemy.top = pos_y+(y_len-10);
	rc_enemy.right = pos_x + 40;
	rc_enemy.bottom = pos_y + y_len;

	rc_score.left = pos_x;
	rc_score.top = pos_y + y_len / 2;
	rc_score.right = pos_x + ENEMY_WIDTH;
	rc_score.bottom = pos_y + y_len / 2 + 1;
}

enemy::enemy(int x)
{
	pos_x = x * (ENEMY_WIDTH + WINDOW_WIDTH) + WINDOW_WIDTH;
	pos_y = MENU_HEIGHT+195;
	is_blink = false;
}

enemy::enemy()
{
}


enemy::~enemy()
{
}
