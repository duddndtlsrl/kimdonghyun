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
			return;
		else if (state % 5 == 1)
			my_rc.bottom = BL_HEIGHT*pt.y + (float)BL_HEIGHT / 2;
		else if (state % 5 == 2)
			my_rc.top = BL_HEIGHT*pt.y + (float)BL_HEIGHT / 2;
		else if (state % 5 == 3)
			my_rc.right = BL_WIDTH*pt.x + (float)BL_WIDTH / 2;
		else
			my_rc.left = BL_WIDTH*pt.x + (float)BL_WIDTH / 2;
	}

	return;
}

void block::get_damage()
{
}

int block::get_state()
{
	return (int)state;
}

POINT block::get_pt()
{
	return pt;
}

block::block()
{
}


block::~block()
{
}
