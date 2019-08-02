#include "game_manager.h"
#include "res_manager.h"
#include "block.h"
#include "block_nature.h"
#include "tank.h"

game_manager* game_manager :: instance = NULL;


void game_manager::init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	SetTimer(hWnd, 1, 3000, NULL);
	res_manage = new res_manager();
	res_manage->init(hdc);
	tanks.reserve(30);
	//tank* p = new tank();
	//p->init(0, 0);
	//tanks.push_back(p);
	load_map();
	
	cur_time = GetTickCount();
	last_time = GetTickCount();

	return;
}

void game_manager::input(float delta_time)
{
	
	if (GetKeyState(VK_UP) & 0x8000)
	{

	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{

	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{

	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{

	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{

	}

}

void game_manager::is_collide(tank* my)
{
	for (auto iter = blocks.begin(); iter != blocks.end(); iter++)
	{
		if ((*iter)->get_state() == BLOCK_END)
			continue;
		(*iter)->
	}
}

bool game_manager::set_enemy()
{
	enemy_count++;
	if (enemy_count == 21)
		return false;
	tank* p = new tank();
	if (enemy_count % 3 == 1)
		p->init(6, 0, true);
	else if (enemy_count % 3 == 2)
		p->init(12, 0, true);
	else
		p->init(0, 0, true);
	tanks.push_back(p);
		
	return true;
}

void game_manager::update(HWND hWnd)
{
	cur_time = GetTickCount();
	delta_time = (cur_time - last_time)/1000.f;
	last_time = cur_time;
	
	HDC hdc = GetDC(hWnd);
	res_manage->draw(hdc, &blocks);
	ReleaseDC(hWnd, hdc);
	return;
}

void game_manager::load_map()
{
	blocks.reserve(300);
	block* p;

	char ch[6];
	wsprintf(ch, "map_%d", stage);
	HANDLE hfile = CreateFile(ch, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			DWORD writeB;
			int stat;
			p = new block();
			ReadFile(hfile, &stat, sizeof(int), &writeB, NULL);
			if (stat >= BLOCK_ICE && stat<BLOCK_HQ)
			{
				block_nature* q = new block_nature();
				q->set_attribute(stat);
				p = q;
			}
			p->init(stat, j, i);
			blocks.push_back(p);
		}
	}
	CloseHandle(hfile);
}

game_manager::game_manager()
{
}


game_manager::~game_manager()
{
}
