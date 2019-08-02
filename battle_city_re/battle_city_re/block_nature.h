#pragma once
#include"block.h"

class block_nature:public block
{
private:
	bool is_bush = false;
	bool is_lake = false;
	bool is_ice = false;
public:
	void set_attribute(int stat);
	void get_damage();
	block_nature();
	~block_nature();
};

