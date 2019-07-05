#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

class bitmap;
class cell;
class res_manager;
class game_manager
{
private:
	HWND hwnd;
	static game_manager* instance;
	vector <cell*> cells;
	res_manager* res_manage;
	bitmap* front;
	bitmap* flag;
	bool end_flag;
	bool win_game;
	int size;
	int mine_max;
	game_manager();
public:
	static game_manager* get_instance();
	bitmap* change_back(int x);
	bool game_end();
	void left_click(int x, int y);
	void right_click(int x, int y);
	void init(HWND hWnd, HDC hdc, HINSTANCE hinstance);
	void flip_mine();
	void flip_near(int x, int y);
	void near_mine(int x, int y);
	void recursive(int x, int y);
	void draw(HDC hdc);
	void make_cell();
	bool flag_all_mine();
	inline void lose_game()
	{
		end_flag = true;
	}
	void cell_release(int siz, int min);
	void release();
	~game_manager();
};

