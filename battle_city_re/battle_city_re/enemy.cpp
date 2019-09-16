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
	
	if (cur_tile[1].y >= pos_hq.y)
	{
		if (cur_tile[1].x > pos_hq.x)
			prior_dir = DIR_LEFT;
		if (cur_tile[0].x < pos_hq.x)
			prior_dir = DIR_RIGHT;
	}

	return;
}

void enemy::search_area()
{
	if (last_dir == DIR_LEFT)
		last_dir=DIR_LEFT;
	
	int randm[4];
	memset(randm, 0, sizeof(int) * 4);
	int count = 0;

	for (int i = DIR_UP; i < DIR_END; i++)
	{
	
		direction = (DIR)i;

		if (game_manager::get_instance()->is_collide(this))
			continue;
		else
		{
			randm[i - 1] = i;
			count++;
		}
	}/*갈 수 있는 방향을 찾아보자*/

	if (randm[(int)last_dir - 1] != 0)
	{
		direction = last_dir;
		if (randm[(int)prior_dir - 1] != 0)
			direction = prior_dir;

		return;
	}


	srand(GetTickCount());

	

	while(true)
	{
		int num = (rand() % 99) + 1;
		int dir;
		
		if (num >= 1 && num < 25)
			dir = 1;
		if (num >= 25 && num < 50)
			dir = 2;
		if (num >= 50 && num < 75)
			dir = 3;
		if (num >= 75 && num < 100)
			dir = 4;
		
		if (randm[dir - 1] != 0)
		{
			direction = (DIR)randm[dir - 1];
			last_dir = direction;
			break;
		}
	}

	frame = 0;

	return;
}

enemy::enemy()
{
	pos_hq.x = 6;
	pos_hq.y = 11;
	last_dir = DIR_DOWN;
	prior_dir = DIR_DOWN;
}


enemy::~enemy()
{
}
