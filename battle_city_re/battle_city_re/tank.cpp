#include "tank.h"
#include "res_manager.h"



void tank::init(float x, float y, bool enemy)
{
	if (!enemy)
	{
		pos_x = x;
		pos_y = y;
	}
	else
		/*利攀农 积己窃荐*/
	is_enemy = enemy;

	set_rc();
}

void tank::set_rc()
{
	my_rc.top = pos_y;
	my_rc.bottom = pos_y + BL_HEIGHT;
	my_rc.left = pos_x;
	my_rc.right = pos_x + BL_WIDTH;
}

void tank::move(float delta_time, int dir = 0)
{
	if (!is_enemy)
	{
		srand(GetTickCount());
		int num = rand() % 4;

		direction = (DIR)num;

		if (num == 0)
			pos_y += delta_time*-100;
		else if (num == 1)
			pos_y += delta_time * 100;
		else if (num == 2)
			pos_x+= delta_time*-100;
		else
			pos_x += delta_time*100;
	}
	else
	{
		direction = (DIR)dir;

		if (dir == 0)
			pos_y += delta_time*-100;
		else if (dir == 1)
			pos_y += delta_time * 100;
		else if (dir == 2)
			pos_x += delta_time*-100;
		else
			pos_x += delta_time * 100;

	}

	set_rc();

}

tank::tank()
{
}


tank::~tank()
{
}
