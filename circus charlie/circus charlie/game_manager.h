#pragma once
#include <Windows.h>
#include <vector>

#define WINDOW_WIDTH 540
#define PI	3.141592f
using namespace std;

class enemy;
class res_manager;
class bitmap;
class player;
class cash;

enum STATE {
	STATE_GROUND,
	STATE_JUMP,
	STATE_MOVE,
	STATE_UP,
	STATE_RIGHT,
	STATE_LEFT
};

class game_manager
{
private:
	static game_manager* instance;
	game_manager();
	DWORD last_time;
	DWORD bonus_time;
	DWORD cur_time;
	STATE state;
	STATE state1;
	RECT rc_temp;
	RECT rc_goal;
	float delta_time;
	float delta_time1;
	float jump_time;
	float start_x;
	float start_y;
	float start_point;
	float progress;
	float count;
	int run_count;
	int score;
	int bonus;
	bool game_flag;
	bool score_flag;
	bool money_flag;
	HBITMAP back_bit;
	vector<enemy*> enemies;
	res_manager* res_manage;
	player* p_player;
	cash* p_cash;
public:
	inline static game_manager* get_instance()
	{
		if (instance == nullptr)
			instance = new game_manager();
		return instance;
	}
	void init(HDC hdc);
	void game_over();
	void refresh();
	void prepare_game();
	void update(HWND hWnd);
	void draw(HDC hdc);
	bool input();
	bool jumping();
	~game_manager();
};

