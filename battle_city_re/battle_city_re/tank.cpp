#include "tank.h"
#include "res_manager.h"
#include "game_manager.h"



void tank::init(float x, float y)
{
	
	pos_x = x;
	pos_y = y;

	set_rc();
}

void tank::set_rc()
{
	my_rc.top = pos_y;
	my_rc.bottom = pos_y + BL_HEIGHT;
	my_rc.left = pos_x;
	my_rc.right = pos_x + BL_WIDTH;

	set_point();
}

void tank::set_point()
{
	mid_point.x = (my_rc.right - my_rc.left) / 2;
	mid_point.y = (my_rc.bottom - my_rc.top) / 2;
}

void tank::move(float delta_time, int dir)
{
	direction = (DIR)dir;
	
	if (game_manager::get_instance()->is_collide(this))
		return;

	if (direction == DIR_UP)
		pos_y += delta_time*-100;
	else if (direction == DIR_DOWN)
		pos_y += delta_time * 100;
	else if (direction == DIR_LEFT)
		pos_x+= delta_time*-100;
	else
		pos_x += delta_time*100;

	end_line();
	

	set_rc();

	return;

}

BOOL tank::is_collide(DF* point)
{
	if (sqrt(pow(mid_point.x - point->x, 2) + pow(mid_point.y - point->y, 2)) < BL_WIDTH)
		return true;
	
	return false;
}

RECT * tank::get_rc()
{
	return &my_rc;
}

DF * tank::get_p()
{
	return &mid_point;
}

int tank::get_dir()
{
	return (int)direction;
}

void tank::set_cur_tile()
{
	cur_tile[0].x = pos_x / BL_WIDTH;
	cur_tile[1].x = cur_tile[0].x;

	cur_tile[0].y = pos_y / BL_WIDTH;
	cur_tile[1].y = cur_tile[0].y;
	
	if ((int)pos_x%BL_WIDTH != 0)
		cur_tile[1].x += 1;

	if ((int)pos_y%BL_WIDTH != 0)
		cur_tile[1].y += 1;


	return;
}

void tank::correct_pos(RECT* rc)
{
	if (direction == DIR_UP)
		pos_y = rc->bottom;
	else if (direction == DIR_DOWN)
		pos_y = rc->top-BL_HEIGHT;
	else if (direction == DIR_LEFT)
		pos_x = rc->right;
	else
		pos_x = rc->left-BL_WIDTH;

	return;
}

bool tank::end_line()
{
	if (pos_x < 0)
		pos_x = 0;
	else if (pos_x > BL_WIDTH * 12)
		pos_x = BL_WIDTH * 12;
	else if (pos_y < 0)
		pos_y = 0;
	else if (pos_y > BL_HEIGHT * 12)
		pos_y = BL_HEIGHT * 12;
	else
		return false;

	return true;

}

void tank::get_pos(float & x, float & y)
{
	x = pos_x;
	y = pos_y;
}

BOOL tank::dead()
{
	if (is_dead)
		return true;
	return false;
}

tank::tank()
{
}


tank::~tank()
{
}

