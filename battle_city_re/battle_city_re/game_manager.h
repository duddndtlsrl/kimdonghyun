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
class game_manager
{
private:
	static game_manager* instance;
	tank* player;
	res_manager* res_manage;
	block* blocks[13][13];
	vector<tank*> tanks;
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
	POINT where_player();
	bool set_enemy();
	game_manager();
	~game_manager();
};

