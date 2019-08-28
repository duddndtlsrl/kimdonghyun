#include "enemy.h"
#include "game_manager.h"
#include "res_manager.h"


void enemy::move(float delta_time)
{
	pos_player = game_manager::get_instance()->where_player();
	
	search_area(delta_time);

	if (direction == DIR_UP)
		pos_y += delta_time*-100;
	else if (direction == DIR_DOWN)
		pos_y += delta_time * 100;
	else if (direction == DIR_LEFT)
		pos_x += delta_time*-100;
	else if (direction == DIR_RIGHT)
		pos_x += delta_time * 100;
	else
		return;

	tank::end_line();
	
	set_rc();

	return;
}

void enemy::search_area(float delta_time)
{
	int randm[4];
	memset(randm, 0, sizeof(int) * 4);

	for (int i = DIR_UP; i < DIR_END; i++)
	{
	
		direction = (DIR)i;
		pos_x = compare_x;
		pos_y = compare_y;
		
		int j = 1;
		if (i % 2 == 1)
			j = -1;
		
		if (i > DIR_DOWN)
			pos_x += j*delta_time * 100;
		else
			pos_y += j*delta_time * 100;

		if (game_manager::get_instance()->is_collide(this) || end_line())
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

bool enemy::end_line()
{
	if (compare_x < 0 || compare_x > BL_WIDTH * 12 || compare_y < 0 || compare_y > BL_HEIGHT * 12)
		return true;

	return false;
}

enemy::enemy()
{
}


enemy::~enemy()
{
}
