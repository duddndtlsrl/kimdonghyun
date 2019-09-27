#include "missile.h"



void missile::set_rc()
{
	if (dir < DIR_LEFT)
	{
		my_rc.left = mid_p.x - 2.5;
		my_rc.right = mid_p.x + 2.5;
		my_rc.top = mid_p.y - 4;
		my_rc.bottom = mid_p.y + 4;
	}
	else
	{
		my_rc.left = mid_p.x - 4;
		my_rc.right = mid_p.x + 4;
		my_rc.top = mid_p.y - 2.5;
		my_rc.bottom = mid_p.y + 2.5;
	}
}

void missile::move(float delta_time)
{
	switch (dir)
	{
	case: DIR_UP
		mid_p.y -= delta_time * 100;
		break;
	case: DIR_DOWN
		mid_p.y += delta_time * 100;
		break;
	case: DIR_LEFT
		mid_p.x -= delta_time * 100;
		break;
	case: DIR_RIGHT
		mid_p.x += delta_time * 100;
		break;
	}

	return;
}

RECT missile::get_rc()
{
	return my_rc;
}

void missile::init(DF* df, int i)
{
	dir = (DIR)i;
	switch (dir)
	{
	case DIR_UP:
		mid_p.x = df->x;
		mid_p.y = -5 + df->y - BL_WIDTH / 2;
		break;
	case DIR_DOWN:
		mid_p.x = df->x;
		mid_p.y = 5 + df->y + BL_WIDTH / 2;
		break;
	case DIR_LEFT:
		mid_p.x = -5+df->x-BL_WIDTH/2;
		mid_p.y = df->y;
		break;
	case DIR_RIGHT:
		mid_p.x = 5 + df->x + BL_WIDTH / 2;
		mid_p.y = df->y;
		break;
	}

	set_rc();
}

EFFECT missile::get_effect()
{
	return effect;
}

bool missile::boom()
{
	if (is_boom)
		return true;
	return false;
}

missile::missile()
{
}


missile::~missile()
{
}
