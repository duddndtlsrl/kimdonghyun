#pragma once
#include <Windows.h>
#include <vector>

#define BL_WIDTH 50
#define BL_HEIGHT 50

using namespace std;

typedef struct doublefloat {
	
	bool operator |(doublefloat a)
	{
		return a.x == x || a.y == y;
	}

	float x;
	float y;
}DF;



enum BLOCK
{
	BLOCK_BRICK_W,
	BLOCK_BRICK_U,
	BLOCK_BRICK_D,
	BLOCK_BRICK_L,
	BLOCK_BRICK_R,
	BLOCK_STONE_W,
	BLOCK_STONE_U,
	BLOCK_STONE_D,
	BLOCK_STONE_L,
	BLOCK_STONE_R,
	BLOCK_ICE,
	BLOCK_BUSH,
	BLOCK_LAKE,
	BLOCK_HQ,
	BLOCK_HQ_DESTROY,
	BLOCK_END
};

enum PLAYER
{
	PLAYER_U_0,
	PLAYER_U_1,
	PLAYER_D_0,
	PLAYER_D_1,
	PLAYER_L_0,
	PLAYER_L_1,
	PLAYER_R_0,
	PLAYER_R_1,
	PLAYER_END
};

enum ENEMY
{
	ENEMY_U_0,
	ENEMY_U_1,
	ENEMY_D_0,
	ENEMY_D_1,
	ENEMY_L_0,
	ENEMY_L_1,
	ENEMY_R_0,
	ENEMY_R_1,
	ENEMY_END
};

enum OBJECT
{
	OBJECT_MISSILE,
	OBJECT_END
};

enum EFFECT
{
	EFFECT_SHIELD_0,
	EFFECT_SHIELD_1,
	EFFECT_EX_MISSILE_0,
	EFFECT_EX_MISSILE_1,
	EFFECT_EX_TANK_0,
	EFFECT_EX_TANK_1,
	EFFECT_EX_TANK_2,
	EFFECT_END
};

enum ICON
{
	ICON_PLAYER,
	ICON_ENEMY,
	ICON_STAGE,
	ICON_END
};
class block;
class tank;
class bitmap;
class res_manager
{
private:
	bitmap* block_bit[BLOCK_END];
	bitmap* player_bit[PLAYER_END];
	bitmap* enemy_bit[ENEMY_END];
	bitmap* effect_bit[EFFECT_END];
	bitmap* icon_bit[ICON_END];
	bitmap* object_bit[OBJECT_END];
public:
	void init(HDC hdc);
	void draw(HDC hdc, block* blocks[][13], vector<tank*>* tanks);
	res_manager();
	~res_manager();
};

