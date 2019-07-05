#pragma once
#include "cell.h"

class mine: public cell
{
public:
	void flip_cell();
	inline void flip_myself()
	{
		open = true;
	}
	mine();
	~mine();
};

