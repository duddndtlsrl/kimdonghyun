#pragma once
#include "tank.h"
class enemy :public tank
{
private:
	POINT pos_player;
	float compare_x;
	float compare_y;
	DIR last_dir;
public:
	void move(float delta_time);
	void search_area();
	enemy();
	~enemy();
};

