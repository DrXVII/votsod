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
		/* The switch is left here as it will handle more functionality in the
		 * future. */
		switch(cmd){
			case KEY_LEFT:
				return cmd;
			case KEY_RIGHT:
				return cmd;
			case KEY_UP:
				return cmd;
			case KEY_DOWN:
				return cmd;
			case 'q': return cmd;
		}
	}while(cmd != 'q');
	return cmd;
}
