#include "Actor_Human.h"

Actor_Human::Actor_Human(int _x, int _y): Actor(_x, _y)
{
	m_icon = '@';
}

Actor_Human::~Actor_Human() {}

int Actor_Human::take_turn()
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
