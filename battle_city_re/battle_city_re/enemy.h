#pragma once
#include "tank.h"
class enemy :public tank
{
private:
	POINT pos_hq;
	DIR prior_dir;
	int frame = 0;
public:
	void move(float delta_time, int dir=0);
	void search_area();
	enemy();
	~enemy();
};

