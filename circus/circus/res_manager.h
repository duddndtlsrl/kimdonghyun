#pragma once
#include <Windows.h>

enum BACK_GROUND {
	BACK_GROUND_UP,
	BACK_GROUND_UP1,
	BACK_GROUND_UP2,
	BACK_GROUND_DOWN,
	BACK_GROUND_END
};

enum PLAYER {
	PLAYER_RUN,
	PLAYER_RUN1,
	PLAYER_JUMP,
	PLAYER_CEREMONY,
	PLAYER_CEREMONY1,
	PLAYER_DIE,
	PLAYER_END
};

class bitmap;

class res_manager
{
	bitmap* back_gr[3];
	bitmap* player[6];
public:
	inline bitmap* get_back(int i)
	{
			return back_gr[i];
	}
	inline bitmap* get_player(int i)
	{
		return player[i];
	}
	void init(HDC hdc, HINSTANCE hinst);
	res_manager();
	~res_manager();
};

