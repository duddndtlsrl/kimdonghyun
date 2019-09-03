#pragma once
#include "res_manager.h"

class block
{
protected:
	BLOCK state;
	POINT pt;
	DF mid_point;
	RECT my_rc;
public:
	void init(int stat, float pos_x, float pos_y);
	void set_rc();
	void set_point();
	DF* get_p();
	virtual void get_damage();
	int get_state();
	POINT get_pt();
	RECT* get_rc();
	block();
	~block();
};

