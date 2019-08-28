#include "game_manager.h"
#include "res_manager.h"
#include "block.h"
#include "block_nature.h"
#include "tank.h"
#include "enemy.h"


game_manager* game_manager :: instance = NULL;


void game_manager::init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	SetTimer(hWnd, 1, 3000, NULL);
	res_manage = new res_manager();
	res_manage->init(hdc);
	tanks.reserve(30);
	tank* p = new tank();
	player = p;
	p->init(0, 0);
	tanks.push_back(p);
	load_map();
	
	cur_time = GetTickCount();
	last_time = GetTickCount();

	return;
}

void game_manager::input()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{

	}

	int dir;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		dir = 1;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		dir = 2;
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		dir = 3;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		dir = 4;
	}
	else
	{
		return;
	}
	
	player->move(delta_time, dir);

	return;
}

bool game_manager::is_collide(tank* my)
{
	RECT rc_temp;
	enemy* p = dynamic_cast<enemy*>(my);
	
	for (auto iter = blocks.begin(); iter != blocks.end(); iter++)
	{
		if ((*iter)->get_state() == BLOCK_END || (*iter)->get_state()==BLOCK_BUSH)
			continue;
		
		if (my->is_collide((*iter)->get_p()))
		{
			return true;
		}
	}

	return false;
}

POINT game_manager::where_player()
{
	float x, y;
	player->get_pos(x, y);
	POINT pt;
	pt.x = x/BL_WIDTH;
	pt.y = y/BL_HEIGHT;
	return pt;
}

bool game_manager::set_enemy()
{
	enemy_count++;
	if (enemy_count == 2)
		return false;
	enemy* q=new enemy();
	tank* p = new tank();
	p = q;
	if (enemy_count % 3 == 1)
		p->init(6*BL_WIDTH, 0);
	else if (enemy_count % 3 == 2)
		p->init(12*BL_WIDTH, 0);
	else
		p->init(0, 0);
	tanks.push_back(p);
		
	return true;
}

void game_manager::update(HWND hWnd)
{
	cur_time = GetTickCount();
	delta_time = (cur_time - last_time)/1000.f;
	last_time = cur_time;
	input();
	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		enemy* p = dynamic_cast<enemy*>(*iter);
		if (p != NULL)
			p->move(delta_time);
	}
	
	HDC hdc = GetDC(hWnd);
	res_manage->draw(hdc, &blocks, &tanks);
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
