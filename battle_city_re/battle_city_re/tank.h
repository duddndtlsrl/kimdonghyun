#pragma once
#include<Windows.h>
#include"res_manager.h"

enum DIR {
	DIR_UP=1,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_END
};

class tank
{
protected:
	float pos_x;
	float pos_y;
	MP mid_point;
	RECT my_rc;
	DIR direction = DIR_UP;
	bool is_dead=false;
public:
	void init(float x, float y);
	void set_rc();
	void set_point();
	virtual void move(float delta_time, int dir);
	BOOL is_collide(MP* point);
	RECT* get_rc();
	MP* get_p();
	int get_dir();
	void correct_pos(RECT* rc);
	virtual bool end_line();
	void get_pos(float& x, float& y);
	BOOL dead();
	tank();
	~tank();
};

