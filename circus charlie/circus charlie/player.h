#pragma once
#include "res_manager.h"

#define PLAYER_WIDTH 66
#define PLAYER_HEIGHT 63

class bitmap;
class player
{
private:
	bitmap* play[PLAYER_END];
	float pos_x;
	float pos_y;
	bool run;
	bool jump;
	bool is_dead;
	RECT player_rc;
public:
	void init(bitmap* bit, int i);
	void set_pos(float count, float x, float y);
	void draw(HDC back_dc);
	void move_rc();
	void game_over();
	inline RECT* get_rc()
	{
		return &player_rc;
	}
	inline void get_pos(float& x, float& y)
	{
		x = pos_x;
		y = pos_y;
	}
	inline void running()
	{
		if (run)
			run = false;
		else
			run = true;
	}
	inline void set_jump()
	{
		if (jump)
			jump = false;
		else
			jump = true;
	}
	player();
	~player();
};

