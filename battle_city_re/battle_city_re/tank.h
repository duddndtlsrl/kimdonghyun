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
	DF mid_point;
	DF cur_tile[2];
	RECT my_rc;
	RECT small_rc;
	DIR direction = DIR_UP;
	bool is_dead=false;
	bool slip = false;
public:
	void init(float x, float y);
	void set_rc();
	void set_point();
	virtual void move(float delta_time, int dir);
	BOOL is_collide(block* p);
	RECT* get_rc();
	DF* get_p();
	DF* get_tile();
	int get_dir();
	void set_cur_tile(block* blocks[][13], bool enemy=false);
	void correct_pos(RECT* rc);
	bool end_line();
	bool is_slip();
	void get_pos(float& x, float& y);
	BOOL dead();
	tank();
	~tank();
};



