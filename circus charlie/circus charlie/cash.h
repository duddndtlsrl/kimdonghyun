#pragma once
#include <Windows.h>
#include "game_manager.h"

class bitmap;
class cash
{
private:
	bitmap * cash_bit;
	RECT rc_cash;
	float pos_x;
	float pos_y;
	bool touch;
public:
	void init(bitmap* bit);
	void move_rc();
	void draw(HDC back_dc);
	bool is_collide(RECT* rc_temp, RECT* rc_player);
	inline void move(float x, float count, float delta_time)
	{
		if (x > count + WINDOW_WIDTH)
			touch = false;
		pos_x = x + 16;
		move_rc();
	}
	cash();
	~cash();
};

