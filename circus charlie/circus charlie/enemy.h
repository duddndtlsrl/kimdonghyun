#pragma once
#include <Windows.h>
#include "game_manager.h"
#include "res_manager.h"

#define ENEMY_WIDTH 50

class bitmap;
class enemy
{
protected:
	RECT rc_enemy;
	RECT rc_score;
	bitmap* normal;
	bitmap* blink;
	int pos_x;
	int pos_y;
	int y_len;
	bool is_blink;
public:
	void init(bitmap* bit, bitmap* bit1, int y);
	bool is_collide(RECT* rc_temp, RECT* rc_player, bool& score_flag);
	void draw(HDC back_dc);
	void move_rc();
	inline void set_blink()
	{
		if (is_blink)
			is_blink = false;
		else
			is_blink = true;
	}
	inline int get_x()
	{
		return pos_x;
	}
	inline virtual void move(float count, float delta_time)
	{
		if (pos_x < count)
			pos_x = count + WINDOW_WIDTH*2;
		move_rc();
	}
	enemy(int x);
	enemy();
	~enemy();
};

