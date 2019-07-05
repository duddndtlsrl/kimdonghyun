#include <math.h>
#include "game_manager.h"
#include "res_manager.h"
#include "player.h"
#include "bitmap.h"
#include "enemy.h"
#include "enemy_move.h"
#include "cash.h"
#include "Macro.h"

game_manager* game_manager::instance = nullptr;

game_manager::game_manager()
{
}

void game_manager::prepare_game()
{
	game_flag = false;
	score_flag = false;
	money_flag = false;
	bonus = 5000;
	progress = 0.0f;
	score = 0;
	count = 0;
	run_count = 0;
	jump_time = 0.0f;
	state = STATE_GROUND;
	state1 = STATE_UP;

	rc_goal.left = WINDOW_WIDTH * 9 +10;
	rc_goal.top = MENU_HEIGHT + 247+49*2;
	rc_goal.right = WINDOW_WIDTH * 9 + 86 + 76;
	rc_goal.bottom = MENU_HEIGHT + 247 + 49;
	
	p_player = new player();
	for (int i = PLAYER_RUN; i < PLAYER_END; i++)
		p_player->init(res_manage->get_player(i), i);

	p_cash = new cash();
	p_cash->init(res_manage->get_resource(RESOURCE_CASH));

	enemies.reserve(100);
	enemy* p;
	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			p = new enemy_move(i);
			p->init(res_manage->get_enemy(ENEMY_A_NORMAL), res_manage->get_enemy(ENEMY_A_BLINK), 132);
		}
		else
		{
			p = new enemy(i - 3);
			p->init(res_manage->get_enemy(ENEMY_B_NORMAL), res_manage->get_enemy(ENEMY_B_BLINK), 50);
		}
		enemies.push_back(p);
	}
}

void game_manager::init(HDC hdc)
{
	last_time = GetTickCount();
	bonus_time = GetTickCount();
	cur_time = GetTickCount();
	res_manage = new res_manager();
	res_manage->init(hdc);
	prepare_game();
	
}

void game_manager::game_over()
{
	if (game_flag)
	{
		refresh();
		prepare_game();
	}
	return;
}

void game_manager::refresh()
{
	for (auto iter = enemies.begin(); iter != enemies.end(); iter++)
		SAFE_DELETE((*iter));
	enemies.clear();
	SAFE_DELETE(p_player)
}

void game_manager::update(HWND hWnd)
{
	cur_time = GetTickCount();
	delta_time = (cur_time - last_time)/1000.0f;
	delta_time1 = (cur_time - bonus_time) / 1000.0f;
	if (delta_time1 > 1)
	{
		bonus -= 10;
		bonus_time = cur_time;
	}
	last_time = cur_time;
	start_point = count;
	
	float x;
	float y;
	p_player->get_pos(x, y);
	if (x > progress)
		progress = x;

	for (auto iter = enemies.begin(); iter != enemies.end(); iter++)
	{
		(*iter)->move(count, delta_time);
		(*iter)->set_blink();
		if (iter == enemies.begin())
			p_cash->move((*iter)->get_x(), count, delta_time);
		if ((*iter)->is_collide(&rc_temp, p_player->get_rc(), score_flag))
		{
			p_player->game_over();
			game_flag = true;
		}
		else
		{
			if (x == (*iter)->get_x())
				score += 50;
		}
	}
	if (!money_flag)
	{
		if (p_cash->is_collide(&rc_temp, p_player->get_rc()))
		{
			score += 100;
			money_flag = true;
		}
	}

	if (input() || jumping())
	{

		if (!jumping())
			state = STATE_GROUND;

		if (input())
		{
			run_count++;
			if (run_count >= 4)
			{
				p_player->running();
				run_count = 0;
			}
		}
	}

	p_player->get_pos(x, y);
	if(count<WINDOW_WIDTH*9+86)
		count = x - 100.0f;
	if (x > progress)
		score += 10;
	if (count < start_point)
		count = start_point;

	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

bool game_manager::input()
{	
	if (state == STATE_JUMP)
		return false;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		p_player->set_pos(count, -30 * delta_time, 0);
		state = STATE_MOVE;
		state1 = STATE_LEFT;
	}
	
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		p_player->set_pos(count, 30 * delta_time, 0);
		state = STATE_MOVE;
		state1 = STATE_RIGHT;
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (state == STATE_GROUND || state==STATE_MOVE)
		{
			state = STATE_JUMP;
			p_player->set_jump();
			p_player->get_pos(start_x, start_y);
		}
	}
	
	if (state == STATE_GROUND)
		return false;
	
return true;
}

void game_manager::draw(HDC hdc)
{
	res_manage->draw(hdc, score, bonus, count, &enemies, p_player, p_cash);
}
bool game_manager::jumping()
{
	if (state == STATE_JUMP)
	{
		jump_time += delta_time;

		float x = jump_time * 80;
		float y = -1 * sinf(jump_time*PI) * 80;

		if (state1 == STATE_LEFT)
			x *= -1;
 		else if (state1==STATE_UP)
			x *= 0;

		p_player->set_pos(count, start_x + x, start_y + y);

		if (jump_time > 1.0f)
		{
			if (score_flag)
			{
				score_flag = false;
				score += 50;
			}
			money_flag = false;
			jump_time = 0.0f;
			p_player->set_pos(count, start_x + x, MENU_HEIGHT+180);
			p_player->set_jump();
			state = STATE_GROUND;
			state1 = STATE_UP;
		}

		return true;
	}
	return false;
}
game_manager::~game_manager()
{
}
