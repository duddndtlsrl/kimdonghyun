#include "cell.h"
#include "bitmap.h"
#include "game_manager.h"

void cell::init(bitmap * bit, bitmap * bit1, bitmap * bit2, int x, int y)
{
	front = bit;
	back = bit1;
	flag = bit2;
	pos_x = x;
	pos_y = y;
}

void cell::draw(HDC hdc)
{
	if (!open)
	{
		if (selected)
			flag->draw(hdc, pos_x, pos_y);
		else
			front->draw(hdc, pos_x, pos_y);
	}
	else
		back->draw(hdc, pos_x, pos_y);
}

void cell::change_back(bitmap * bit)
{
	back = bit;
}

bool cell::is_near(int x, int y)
{
	if (pos_x == x && pos_y == y)
		return false;
	else if (abs(pos_x - x) <= 1 && abs(pos_y - y) <= 1)
		return true;
	
	return false;
}

void cell::set_minecount()
{
	if (!is_mine)
		mine_count++;
	return;
}

void cell::search_near()
{ 
	game_manager::get_instance()->flip_near(pos_x, pos_y);

}

void cell:: flip_cell()
{
	open = true;
}

void cell::notice_pos(int& x, int& y)
{
	parent = true;
	x = pos_x;
	y = pos_y;
}

void cell::flag_this()
{
	if (open)
		return;
	
	if (selected)
		selected = false;
	else
		selected = true;
}

bool cell::check_pos(int x, int y)
{
	if (pos_x == x && pos_y == y)
		return true;
	return false;
}


cell::cell()
{
	is_mine = false;
	open = false;
	selected = false;
	parent = false;
	mine_count = 0;
}


cell::~cell()
{
}
