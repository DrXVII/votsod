#include "Actor_Human.h"

Actor_Human::Actor_Human(int _x, int _y): Actor(_x, _y)
{
	m_controller = "HUMAN";
	m_icon = '@';
	m_maxhp = 12;
	m_hp = m_maxhp;
	m_dmg = 4;
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
			// if movement key pressed - return move request to map for validation
			case '8':
				return cmd;
			case '2':
				return cmd;
			case '4':
				return cmd;
			case '6':
				return cmd;
			case '5':
				return cmd;
			// END of movement section
			case 'q': return cmd;
		}
	}while(cmd != 'q');
	return cmd;
}
