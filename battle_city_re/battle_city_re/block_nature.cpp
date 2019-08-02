#include "block_nature.h"



void block_nature::set_attribute(int stat)
{
	if (stat == BLOCK_ICE)
		is_ice = true;
	else if (stat == BLOCK_LAKE)
		is_lake = true;
	else
		is_bush = true;
}

void block_nature::get_damage()
{
}

block_nature::block_nature()
{
}


block_nature::~block_nature()
{
}
