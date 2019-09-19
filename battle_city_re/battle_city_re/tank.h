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

enum STATE {
	STATE_GROUND,
	STATE_ICE,
	STATE_EDGE
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
	DIR last_dir;
	STATE state = STATE_GROUND;
	bool is_dead=false;
	bool* flag = nullptr;
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
	void edge_of_ice(block* blocks[][13]);
	bool end_line();
	void get_pos(float& x, float& y);
	STATE get_state();
	BOOL dead();
	tank();
	~tank();
};



