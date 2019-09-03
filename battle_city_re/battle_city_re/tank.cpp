#include "tank.h"
#include "res_manager.h"
#include "game_manager.h"
#include "block.h"


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
	set_cur_tile();
}

void tank::set_point()
{
	mid_point.x = pos_x+(my_rc.right - my_rc.left) / 2;
	mid_point.y = pos_y+(my_rc.bottom - my_rc.top) / 2;
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

void tank::search_area(block* map[][13])
{
	
}

BOOL tank::is_collide(block *p)
{
	float compare;
	
	if (p->get_state() == BLOCK_END || p->get_state() == BLOCK_ICE || p->get_state() == BLOCK_BUSH)
		return false;
	
	if (p->get_state() < BLOCK_ICE)
	{
		if (p->get_state() % 5 != 0)
			compare = BL_WIDTH * 3 / 4;
		else
			compare = BL_WIDTH;
	}
	else 
	{
		compare = BL_WIDTH;
	}

	if (sqrt(pow(mid_point.x - p->get_p()->x, 2) + pow(mid_point.y - p->get_p()->y, 2)) < compare)
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

DF * tank::get_tile()
{
	return cur_tile;
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
	
	if ((int)pos_x%BL_WIDTH < 4 || (int)pos_x%BL_WIDTH>36 || (int)pos_y%BL_WIDTH < 4 || (int)pos_y%BL_WIDTH>36)
		return;

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

