#include "enemy.h"
#include "game_manager.h"
#include "res_manager.h"


void enemy::move(float delta_time, int dir)
{	
	search_area();

	if (direction == DIR_UP)
		pos_y += delta_time*-100;
	else if (direction == DIR_DOWN)
		pos_y += delta_time * 100;
	else if (direction == DIR_LEFT)
		pos_x += delta_time*-100;
	else
		pos_x += delta_time * 100;

	end_line();

	set_rc();
	
	return;
}

void enemy::search_area()
{
	int randm[4];
	memset(randm, 0, sizeof(int) * 4);

	for (int i = DIR_UP; i < DIR_END; i++)
	{
	
		direction = (DIR)i;

		if (game_manager::get_instance()->is_collide(this))
			continue;
		else
			randm[i - 1] = i;
	}

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (randm[i] != 0)
			count++;
	}

	if (count < 3)
	{

		
	}
	
	else 
	{
		for (int i = 0; i < 4; i++)
		{
			
			srand(GetTickCount());
			int num = (rand() % 100) + 1;
			
			

		}
	}
	
	return;
}

enemy::enemy()
{
	pos_hq.x = 6;
	pos_hq.y = 11;
	last_dir = DIR_END;
}


enemy::~enemy()
{
}
