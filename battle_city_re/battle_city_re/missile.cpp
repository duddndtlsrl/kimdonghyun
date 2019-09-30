#include "missile.h"
#include "game_manager.h"



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
	case DIR_UP:
		mid_p.y -= delta_time * 200;
		break;
	case DIR_DOWN:
		mid_p.y += delta_time * 200;
		break;
	case DIR_LEFT:
		mid_p.x -= delta_time * 200;
		break;
	case DIR_RIGHT:
		mid_p.x += delta_time * 200;
		break;
	}

	set_rc();

	return;
}

RECT missile::get_rc()
{
	return my_rc;
}

OBJECT missile::get_object()
{
	return object;
}

void missile::is_collide()
{
	bool tank = false;
	DF df=game_manager::get_instance()->is_collide(&my_rc, mid_p, dir, tank);
	if (df.x == 13 && df.y == 13)
		return;
	else
	{
		if (tank)
			effect=EFFECT_EX_TANK_0;
		else
			effect = EFFECT_EX_MISSILE_0;
		
		object = OBJECT_END;
		mid_p = df;
		is_boom = true;
	}
}

void missile::init(DF* df, int i)
{
	dir = (DIR)i;
	switch (dir)
	{
	case DIR_UP:
		mid_p.x = df->x;
		mid_p.y = -5 + df->y - BL_WIDTH / 2;
		object = OBJECT_MISSILE_U;
		break;
	case DIR_DOWN:
		mid_p.x = df->x;
		mid_p.y = 5 + df->y + BL_WIDTH / 2;
		object = OBJECT_MISSILE_D;
		break;
	case DIR_LEFT:
		mid_p.x = -5+df->x-BL_WIDTH/2;
		mid_p.y = df->y;
		object = OBJECT_MISSILE_L;
		break;
	case DIR_RIGHT:
		mid_p.x = 5 + df->x + BL_WIDTH / 2;
		mid_p.y = df->y;
		object = OBJECT_MISSILE_R;
		break;
	}

	set_rc();
}

EFFECT missile::get_effect()
{
	count++;
	if(!count)
		count = (int)effect;
	effect = (EFFECT)count;
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
