#pragma once
#include <windows.h>

#define CELL_WIDTH 60
#define CELL_HEIGHT 60

class bitmap;
class cell
{
protected:
	bool is_mine;
	bool open;
	bool selected;
	bool parent;
	int pos_x;
	int pos_y;
	int mine_count;
	bitmap* front;
	bitmap* back;
	bitmap* flag;
public:
	void init(bitmap* bit, bitmap* bit1, bitmap* bit2, int x, int y);
	void draw(HDC hdc);
	void change_back(bitmap* bit);
	bool check_pos(int x, int y);
	void notice_pos(int& x, int& y);
	void flag_this();
	inline bool notice_mine()
	{
		if (is_mine)
	  		return true;
		return false;
	} 
	inline bool is_selected()
	{
		if (selected)
			return true;
		return false;
	}
	inline bool is_child()
	{
		if (parent)
			return false;
		return true;
	}
	bool is_near(int x, int y);
	 inline int get_minecount()
	 {
		 return mine_count;
	 }
	 void set_minecount();
	void search_near();
	 virtual void flip_cell();
	cell();
	~cell();
};

