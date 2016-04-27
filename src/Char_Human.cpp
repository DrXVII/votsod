#include "Char_Human.h"

Char_Human::Char_Human(int _x, int _y): Char(_x, _y)
{
	m_icon = '@';
}

Char_Human::~Char_Human()
{
	//dtor
}

int Char_Human::take_turn()
{
	int cmd = ' ';
	do{
		cmd = getch();
		switch(cmd){
			case KEY_LEFT:
				/*if(_M.GetTile(Y, X-1).GetPassable())*/ m_x -= 1;
				return cmd;
			case KEY_RIGHT:
				/*if(_M.GetTile(Y, X+1).GetPassable())*/ m_x += 1;
				return cmd;
			case KEY_UP:
				/*if(_M.GetTile(Y-1, X).GetPassable())*/ m_y -= 1;
				return cmd;
			case KEY_DOWN:
				/*if(_M.GetTile(Y+1, X).GetPassable())*/ m_y += 1;
				return cmd;
			case 'q': return cmd;
		}
	}while(cmd != 'q');
	return cmd;
}
