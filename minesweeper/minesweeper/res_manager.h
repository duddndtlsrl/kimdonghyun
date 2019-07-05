#pragma once
#include <Windows.h>

enum CELL_TYPE {
	CELL_TYPE_FRONT,
	CELL_TYPE_BACK,
	CELL_TYPE_BACK_01,
	CELL_TYPE_BACK_02,
	CELL_TYPE_BACK_03,
	CELL_TYPE_BACK_04,
	CELL_TYPE_BACK_05,
	CELL_TYPE_MINE,
	CELL_TYPE_FLAG,
	CELL_TYPE_END
};

class bitmap;
class res_manager
{
private:
	bitmap* block[9];
public:
	void init(HDC hdc, HINSTANCE hinstance);
	void release();
	inline bitmap* get_cell(int i)
	{
		return block[i];
	}
	res_manager();
	~res_manager();
};

