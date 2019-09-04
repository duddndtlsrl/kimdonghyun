#include "block.h"



void block::init(int stat, float pos_x, float pos_y)
{
	state = (BLOCK)stat;
	pt.x = pos_x;
	pt.y = pos_y;
	set_rc();

	return;
}

void block::set_rc()
{
	
	my_rc.left = BL_WIDTH*pt.x;
	my_rc.right = BL_WIDTH*(pt.x + 1);
	my_rc.top = BL_HEIGHT*pt.y;
	my_rc.bottom = BL_HEIGHT*(pt.y + 1);
		
	if (state < BLOCK_ICE)
	{
		if (state % 5 == 0)
			;
		else if (state % 5 == 1)
			my_rc.bottom = BL_HEIGHT*pt.y + (float)BL_HEIGHT / 2;
		else if (state % 5 == 2)
			my_rc.top = BL_HEIGHT*pt.y + (float)BL_HEIGHT / 2;
		else if (state % 5 == 3)
			my_rc.right = BL_WIDTH*pt.x + (float)BL_WIDTH / 2;
		else
			my_rc.left = BL_WIDTH*pt.x + (float)BL_WIDTH / 2;
	}

	set_point();

	return;
}

void block::set_point()
{
	mid_point.x = my_rc.left+(my_rc.right - my_rc.left) / 2;
	mid_point.y = my_rc.top+(my_rc.bottom - my_rc.top) / 2;
}

DF * block::get_p()
{
	return &mid_point;
}

void block::get_damage()
{
}

int block::get_state()
{
	return (int)state;
}

bool block::is_collide(RECT * rc)
{
	RECT rc_temp;
	if (IntersectRect(&rc_temp, rc, &my_rc))
		return true;

	return false;
}

POINT block::get_pt()
{
	return pt;
}

RECT * block::get_rc()
{
	return &my_rc;
}

block::block()
{
}


block::~block()
{
}
