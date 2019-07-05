#pragma once
#include <Windows.h>

class res_manager;
class bitmap;
class player;

class game_manager
{
private:
	static game_manager* instance;
	game_manager();
	HDC g_hdc;
	HDC back_dc;
	HBITMAP back_bit;
	res_manager* res_manage;
	player* p_player;
public:
	inline static game_manager* get_instance()
	{
		if (instance == nullptr)
			instance = new game_manager();
		return instance;
	}
	void init(HDC hdc, HINSTANCE hinst);
	void draw();
	~game_manager();
};

