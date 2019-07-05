#include "game_manager.h"
#include "Macro.h"
#include "cell.h"
#include "res_manager.h"
#include "mine.h"

game_manager* game_manager :: instance = nullptr;

void game_manager::init(HWND hWnd, HDC hdc, HINSTANCE hinstance)
{
	hwnd = hWnd;
	cells.reserve(1024);
	srand(GetTickCount());
	res_manage = new res_manager();
	res_manage->init(hdc, hinstance);
	front = res_manage->get_cell(CELL_TYPE_FRONT);
	flag = res_manage->get_cell(CELL_TYPE_FLAG);
		
	make_cell();
}

void game_manager::flip_mine()
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->notice_mine())
		{
			mine* m = NULL;
			m = dynamic_cast<mine*>(*iter);
			m->flip_myself();
		}
	}
}

void game_manager::near_mine(int x, int y)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->is_near(x, y))
			(*iter)->set_minecount();
	}
}

void game_manager::flip_near(int x, int y)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->is_near(x, y))
			(*iter)->flip_cell();
	}
}

void game_manager::draw(HDC hdc)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		(*iter)->draw(hdc);
}

void game_manager::make_cell()
{
	int* max = new int[mine_max];
	memset(max, 0, sizeof(int)*mine_max);
	bool* b_max = new bool[size*size];
	memset(b_max, false, pow(size, 2));

	int count = 0;
	while (true)
	{
		int num = rand() % (size*size);
		if (b_max[num] == false)
		{
			max[count] = num;
			b_max[num] = true;
			count++;
		}
		if (count == mine_max)
			break;
	}

	for (int i = 0; i < mine_max; i++)
	{
		int temp;
		for (int j = 0; j < mine_max - i - 1; j++)
		{
			if (max[j] > max[j + 1])
			{
				temp = max[j];
				max[j] = max[j + 1];
				max[j + 1] = temp;
			}
		}
	}

	count = 0;
	cell* p;
	for (int i = 0; i != size; i++)
	{
		for (int j = 0; j != size; j++)
		{
			if (max[count] == size * i + j)
			{
				if (count >= 10)
					break;
				p = new mine();
				p->init(front, res_manage->get_cell(CELL_TYPE_MINE), flag, j, i);
				count++;
			}
			else
			{
				p = new cell();
				p->init(front, res_manage->get_cell(CELL_TYPE_BACK), flag, j, i);
			}
			cells.push_back(p);
		}
	}

	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->notice_mine())
		{
			int x;
			int y;
			(*iter)->notice_pos(x, y);
			near_mine(x, y);
		}

	}

	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		int num = (*iter)->get_minecount();
		if (num > 0)
			(*iter)->change_back(res_manage->get_cell(num + 1));
	}

	delete[] max;
	delete[] b_max;
}

bool game_manager::flag_all_mine()
{
	int count = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->notice_mine())
		{
			if ((*iter)->is_selected())
				count++;
		}
	}
	
	if (count >= mine_max)
		return true;

	return false;
}

void game_manager::recursive(int x, int y)
{
	flip_near(x, y);
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->is_near(x, y))
		{
			if ((*iter)->get_minecount() > 0)
				continue;
			else
			{
				if ((*iter)->is_child())
				{
					(*iter)->notice_pos(x, y);
					recursive(x, y);
				}
			}
		}
	}
}

bitmap * game_manager::change_back(int x)
{
	return res_manage->get_cell(x + 1);
}

bool game_manager::game_end()
{
	if (end_flag)
	{
		if (win_game)
			MessageBox(hwnd, TEXT("승리!"), TEXT("게임 종료"), MB_OK);
		else
			MessageBox(hwnd, TEXT("패배!"), TEXT("게임 종료"), MB_OK);
		return true;
	}
	
	return false;
}

game_manager::game_manager()
{
	end_flag = false;
	win_game = false;
	mine_max = 10;
	size = 9;
}

void game_manager::cell_release(int siz, int min)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		SAFE_DELETE(*iter);
	cells.clear();
	size = siz;
	mine_max = min;
}

void game_manager::release()
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		SAFE_DELETE(*iter);
	res_manage->release();
	SAFE_DELETE(res_manage);
	SAFE_DELETE(instance);
}

game_manager * game_manager::get_instance()
{
	if (instance == nullptr)
		instance = new game_manager();
	return instance;
}

void game_manager::left_click(int x, int y)
{
	x /= CELL_WIDTH;
	y /= CELL_HEIGHT;

	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->check_pos(x, y))
		{
			if ((*iter)->is_selected())
				return;
			
			(*iter)->flip_cell();
			if (!(*iter)->notice_mine())
			{
				if ((*iter)->get_minecount() > 0)
					return;
				else
					recursive(x, y);
			}
		}
	}

}

void game_manager::right_click(int x, int y)
{
	x /= CELL_WIDTH;
	y /= CELL_HEIGHT;

	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if ((*iter)->check_pos(x, y))
		{
			(*iter)->flag_this();
			break;
		}
	}

	if (flag_all_mine())
	{
		end_flag = true;
		win_game = true;
	}
}

game_manager::~game_manager()
{
}
