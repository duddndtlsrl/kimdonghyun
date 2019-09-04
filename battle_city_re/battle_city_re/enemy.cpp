#include "enemy.h"
#include "game_manager.h"
#include "res_manager.h"


void enemy::move(float delta_time)
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
		/*pos_x = compare_x;
		pos_y = compare_y;
		
		int j = 1;
		if (i % 2 == 1)
			j = -1;
		
		if (i > DIR_DOWN)
			pos_x += j*delta_time * 100;
		else
			pos_y += j*delta_time * 100;*/

		if (game_manager::get_instance()->is_collide(this))
			continue;
		else
		{
			if (direction == last_dir)
				return;
			randm[i - 1] = i;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		srand(GetTickCount());
		int num = (rand() % 4) + 1;

		if (randm[num - 1] != 0)
		{
			direction = (DIR)num;
			last_dir = direction;
			break;
		}
		else
			continue;
	}
	
	return;
}

enemy::enemy()
{
}


enemy::~enemy()
{
}
