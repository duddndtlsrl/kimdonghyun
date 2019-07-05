#include "res_manager.h"
#include "bitmap.h"
#include <stdio.h>

void res_manager::init(HDC hdc, HINSTANCE hinstance)
{
	char buffer[20];
	for (int i = 0; i < CELL_TYPE_END; i++)
	{
		if (i == 0)
			sprintf(buffer, "cell.bmp");
		else
			sprintf(buffer, "cell_0%d.bmp", i - 1);
		block[i] = new bitmap();
		block[i]->init(hinstance, hdc, buffer);
	}
}

void res_manager::release()
{
	for (int i = 0; i < CELL_TYPE_END; i++)
		block[i]->release();
}


res_manager::res_manager()
{

}


res_manager::~res_manager()
{
}
