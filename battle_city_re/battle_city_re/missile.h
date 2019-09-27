#pragma once
#include "res_manager.h"
#include "tank.h"
class missile
{
private:
	EFFECT effect;
	DIR dir;
	DF mid_p;
	RECT my_rc;
	int count = 0;
	bool is_boom = false;
public:
	void set_rc();
	RECT get_rc();
	void init(DF* df, int i);
	void move(float delta_time);
	EFFECT get_effect();
	bool boom();
	missile();
	~missile();
};

