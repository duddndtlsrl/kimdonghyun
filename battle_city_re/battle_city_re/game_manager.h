#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

enum COLLIDE
{
	COLLIDE_UP,
	COLLIDE_DOWN,
	COLLIDE_LEFT,
	COLLIDE_RIGHT
};

class tank;
class block;
class res_manager;
class missile;
class game_manager
{
private:
	static game_manager* instance;
	tank* player;
	res_manager* res_manage;
	block* blocks[13][13];
	vector<tank*> tanks;
	vector<missile*> missiles;
	int stage=1;
	int enemy_count = 0;
	float delta_time;
	float cur_time;
	float last_time;
public:
	static game_manager* get_instance()
	{
		if (instance == NULL)
			instance = new game_manager();
		return instance;
	}
	void update(HWND hWnd);
	void init(HWND hWnd);
	void load_map();
	void input();
	bool is_collide(tank* my);
	block* (*get_block())[13];
	POINT where_player();
	bool set_enemy();
	void set_missile(DF* df, int dir);
	game_manager();
	~game_manager();
};

