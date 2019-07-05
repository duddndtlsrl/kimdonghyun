#include "cash.h"
#include "bitmap.h"
#include "res_manager.h"

void cash::init(bitmap * bit)
{
	cash_bit = bit;
	move_rc();
}

void cash::draw(HDC back_dc)
{
	if (touch)
		return;
	cash_bit->draw(back_dc, pos_x, pos_y);
}

bool cash::is_collide(RECT * rc_temp, RECT * rc_player)
{
	if (IntersectRect(rc_temp, rc_player, &rc_cash))
	{
		touch = true;
		return true;
	}
	else
		return false;
}

void cash::move_rc()
{
	rc_cash.left = pos_x;
	rc_cash.top = pos_y;
	rc_cash.right = pos_x + 25;
	rc_cash.bottom = pos_y + 26;
}

cash::cash()
{
	pos_x = WINDOW_WIDTH;
	pos_y = MENU_HEIGHT + 90;
	touch = false;
}

cash::~cash()
{
}
