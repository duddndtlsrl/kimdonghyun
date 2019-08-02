#pragma once
#include "res_manager.h"
class block
{
protected:
	BLOCK state;
	POINT pt;
	RECT my_rc;
public:
	void init(int stat, float pos_x, float pos_y);
	void set_rc();
	virtual void get_damage();
	int get_state();
	POINT get_pt();
	block();
	~block();
};

