#pragma once
#include "res_manager.h"

class bitmap;
class player
{
private:
	bitmap* play[PLAYER_END];
public:
	void init(bitmap* bit, int i);
	player();
	~player();
};

