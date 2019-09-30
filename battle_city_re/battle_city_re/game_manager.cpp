#include "game_manager.h"
#include "res_manager.h"
#include "block.h"
#include "block_nature.h"
#include "tank.h"
#include "enemy.h"
#include "missile.h"


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
	missiles.reserve(100);
	load_map();
	
	cur_time = GetTickCount();
	last_time = GetTickCount();

	return;
}

void game_manager::input()
{	
	int dir = 0;
	player->set_cur_tile(blocks);
	
	if (GetKeyState(VK_UP) & 0x8000)
	{
		dir = 1;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		dir = 2;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		dir = 3;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		dir = 4;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (player->get_count() >= 300)
		{
			float x, y;
			player->get_pos(x, y);
			if (dir == 0)
				set_missile(player->get_p(), player->get_dir());
			else
				set_missile(player->get_p(), dir);
		}
	}

	if(dir==0)
	{
		if (player->get_state() != STATE_ICE)
			return;	
	}
	
	player->move(delta_time, dir);

	return;
}

bool game_manager::is_collide(tank* my)
{
	
	int direct = my->get_dir();

	int x, y, x1, y1;

	if (direct == 1)
	{
		x = (int)my->get_tile()[0].x;
		x1 = (int)my->get_tile()[1].x;
		y = (int)my->get_tile()[1].y-1;
		y1 = y;
	}
	if (direct == 2)
	{
		x = (int)my->get_tile()[0].x;
		x1 = (int)my->get_tile()[1].x;
		y = (int)my->get_tile()[0].y+1;
		y1 = y;
	}
	if (direct == 3)
	{
		y = (int)my->get_tile()[0].y;
		y1 = (int)my->get_tile()[1].y;
		x = (int)my->get_tile()[1].x-1;
		x1 = x;
	}
	if (direct == 4)
	{
		y = (int)my->get_tile()[0].y;
		y1 = (int)my->get_tile()[1].y;
		x = (int)my->get_tile()[0].x+1;
		x1 = x;
	}

	if (x < 0 || x>12 || y < 0 || y>12)
		return true;
	
	if (my->is_collide(blocks[y][x]))
		return true;
	else if (my->is_collide(blocks[y1][x1]))
		return true;

	return false;
}

DF game_manager::is_collide(RECT * rc, DF mid, DIR dir, bool& tank)
{
	RECT rc_temp;
	DF df; df.x = 13, df.y = 13;
	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		if (IntersectRect(&rc_temp, rc, (*iter)->get_rc()))
		{
			(*iter)->set_dead(true);
			df = *((*iter)->get_p());
			tank = true;
			return df;
		}
	}
	
	int pos_x=mid.x / BL_WIDTH, pos_y=mid.y / BL_HEIGHT;
	
	if (pos_x < 0 || pos_x>12)
	{
		if (dir == DIR_LEFT)
			df.x = 0, df.y = mid.y;
		if (dir == DIR_RIGHT)
			df.x = 12, df.y = mid.y;

		return df;
	}

	if (pos_y < 0 || pos_y>12)
	{
		if (dir == DIR_UP)
			df.x = mid.x, df.y = 0;
		if (dir == DIR_DOWN)
			df.x = mid.x, df.y = 12;

		return df;
	}



	for (int i = 0; i < 13; i++)
	{
		if (dir < DIR_LEFT && IntersectRect(&rc_temp, rc, blocks[i][pos_x]->get_rc()))
			if (blocks[i][pos_x]->get_damage((int)dir))
			{
				df = *blocks[i][pos_x]->get_p();
				break;
			}
		if(dir>DIR_DOWN && IntersectRect(&rc_temp, rc, blocks[pos_y][i]->get_rc()))
			if (blocks[pos_y][i]->get_damage((int)dir))
			{
				df = *blocks[pos_y][i]->get_p();
				break;
			}
	}

	return df;
}

block *(*game_manager::get_block())[13]
{
	return blocks;
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
	/*enemy_count++;
	if (enemy_count == 10)
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
	tanks.push_back(p);*/
		
	return true;
}

void game_manager::set_missile(DF* df, int dir)
{
	missile* p = new missile();
	p->init(df, dir);
	missiles.push_back(p);

	return;
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
		{
			p->set_cur_tile(blocks, true);
			p->move(delta_time);
		}
	}
	for (auto iter = missiles.begin(); iter != missiles.end(); iter++)
	{
		if ((*iter)->get_object() == OBJECT_END)
			continue;
		(*iter)->move(delta_time);
		(*iter)->is_collide();
	}

	HDC hdc = GetDC(hWnd);
	res_manage->draw(hdc, blocks, &tanks, &missiles);
	ReleaseDC(hWnd, hdc);
	return;
}

void game_manager::load_map()
{

	char ch[6];
	wsprintf(ch, "map_%d", stage);
	HANDLE hfile = CreateFile(ch, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			DWORD writeB;
			int stat;
			blocks[i][j] = new block();
			ReadFile(hfile, &stat, sizeof(int), &writeB, NULL);
			if (stat >= BLOCK_ICE && stat<BLOCK_HQ)
			{
				block_nature* q = new block_nature();
				q->set_attribute(stat);
				blocks[i][j] = q;
			}
			
			if (i == 1)
				int a=0;
			
			blocks[i][j]->init(stat, j, i);
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
