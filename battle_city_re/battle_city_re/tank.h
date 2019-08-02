#pragma once
#include<Windows.h>

enum DIR {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

class tank
{
private:
	float pos_x;
	float pos_y;
	RECT my_rc;
	DIR direction = DIR_UP;
	bool is_enemy;
public:
	void init(float x, float y, bool enemy = false);
	void set_rc();
	void move(float delta_time, int dir=0);
	tank();
	~tank();
};

