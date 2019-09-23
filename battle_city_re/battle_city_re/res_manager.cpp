#include "res_manager.h"
#include "bitmap.h"
#include "block.h"
#include"tank.h"
#include "block_nature.h"
#include "enemy.h"
#include "missile.h"

void res_manager::init(HDC hdc)
{	
	char* ch= new char[20];
	for (int i = 0; i < BLOCK_END; i++)
	{
		block_bit[i] = new bitmap();
		if (i < 10)
			wsprintf(ch, "block0%d.bmp", i);
		else
			wsprintf(ch, "block%d.bmp", i);
		block_bit[i]->init(hdc, ch);
	}
	for (int i = 0; i < PLAYER_END; i++)
	{
		player_bit[i] = new bitmap();
		wsprintf(ch, "p_move_0%d.bmp", i);
		player_bit[i]->init(hdc, ch);
	}
	for (int i = 0; i < ENEMY_END; i++)
	{
		enemy_bit[i] = new bitmap();
		wsprintf(ch, "e_move_0%d.bmp", i);
		enemy_bit[i]->init(hdc, ch);
	}
	for (int i = 0; i < OBJECT_END; i++)
	{
		object_bit[i] = new bitmap();
		wsprintf(ch, "missile.bmp");
		object_bit[i]->init(hdc, ch);
	}
	for (int i = 0; i < EFFECT_END; i++)
	{
		effect_bit[i] = new bitmap();
		wsprintf(ch, "shield_0%d.bmp", i);
		if(i>=EFFECT_EX_MISSILE_0)
			wsprintf(ch, "explosion_0%d.bmp", i-2);
		effect_bit[i]->init(hdc, ch);
	}
	for (int i = 0; i < ICON_END; i++)
	{
		icon_bit[i] = new bitmap();
		wsprintf(ch, "icon_0%d.bmp", i);
		icon_bit[i]->init(hdc, ch);
	}

	return;
}

void res_manager::draw(HDC hdc, block* blocks[][13], vector<tank*>* tanks, vector<missile*>* missiles)
{
	bitmap* back_bit=new bitmap();
	back_bit->init(hdc, "", true);
	
	for (int i = 0; i < 13; i++)
	{
		for(int j=0; j<13; j++)
		{
			if (blocks[i][j]->get_state() == BLOCK_BUSH || blocks[i][j]->get_state() == BLOCK_END)
				continue;
			
			block_bit[blocks[i][j]->get_state()]->draw(back_bit->get_dc(), blocks[i][j]->get_pt().x, blocks[i][j]->get_pt().y, false, true);
		}
	}
	for (auto iter = tanks->begin(); iter != tanks->end(); iter++)
	{
		if ((*iter)->dead())
			continue;
		else
		{
			float x, y;
			(*iter)->get_pos(x, y);
			enemy* p = dynamic_cast<enemy*>(*iter);
			if (p!=NULL)
				enemy_bit[(p->get_dir()-1)*2]->draw(back_bit->get_dc(), x, y);
			else
				player_bit[((*iter)->get_dir()-1)*2]->draw(back_bit->get_dc(), x, y);
		}
	}
	for (auto iter = missiles->begin(); iter != missiles->end(); iter++)
	{
		if ((*iter)->boom())
			object_bit[OBJECT_MISSILE]->draw(back_bit->get_dc(), (*iter)->get_rc().left, (*iter)->get_rc().top);
		else
		{
			effect_bit[(*iter)->get_effect()]->draw(back_bit->get_dc(), (*iter)->get_rc().left, (*iter)->get_rc().top);
		}
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (blocks[i][j]->get_state() == BLOCK_BUSH)
				block_bit[blocks[i][j]->get_state()]->draw(back_bit->get_dc(), blocks[i][j]->get_pt().x, blocks[i][j]->get_pt().y, false, true);
		}
	}

	back_bit->draw(hdc, 0, 0, true, false);
	delete(back_bit);
	

	return;
}

res_manager::res_manager()
{
}


res_manager::~res_manager()
{
}
