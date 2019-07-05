#pragma once
#include "enemy.h"

class enemy_move :public enemy
{
public:
	inline void move(float count, float delta_time)
	{
		pos_x -= delta_time * 50;
		if (pos_x < count)
			pos_x = count + WINDOW_WIDTH*5/2;
		move_rc();
	}
	enemy_move(int x);
	~enemy_move();
};

