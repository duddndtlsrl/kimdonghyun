#include "mine.h"
#include "game_manager.h"

void mine::flip_cell()
{
	open = true;
	game_manager::get_instance()->flip_mine();
	game_manager::get_instance()->lose_game();
}

mine::mine()
{
	is_mine = true;
}

mine::~mine()
{
}
