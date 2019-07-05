#pragma once
#include <Windows.h>
#include <vector>

#define MENU_HEIGHT 50
using namespace std;

class enemy;
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

enum ENEMY {
	ENEMY_A_NORMAL,
	ENEMY_A_BLINK,
	ENEMY_B_NORMAL,
	ENEMY_B_BLINK,
	ENEMY_END
};

enum RESOURCE {
	RESOURCE_METER,
	RESOURCE_CASH,
	RESOURCE_GOAL,
	RESOURCE_END
};

class bitmap;
class player;
class cash;
class res_manager
{
	bitmap* back_gr[BACK_GROUND_END];
	bitmap* players[PLAYER_END];
	bitmap* enemy_bit[ENEMY_END];
	bitmap* resource[RESOURCE_END];
	HDC back_dc;
	HBITMAP back_bit;
	HBITMAP old_bit;
public:
	inline bitmap* get_player(int i)
	{
		return players[i];
	}
	inline bitmap* get_enemy(int i)
	{
		return enemy_bit[i];
	}
	inline bitmap* get_resource(int i)
	{
		return resource[i];
	}
	void init(HDC hdc);
	void draw(HDC hdc, int score, int bonus, float count, vector<enemy*>* enemies, player* p_player, cash* p_cash);
	res_manager();
	~res_manager();
};

