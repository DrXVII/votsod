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
	int cmd = 0;
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

int Actor_Human::take_turn2(const vector<vector<Tile*>>& _tiles)
{
	int cmd = 0;
	unsigned int new_y;
	unsigned int new_x;
	
	do{
		new_y = m_y;
		new_x = m_x;
		
		cmd = getch();
		switch(cmd){
			// if movement key pressed - return move request to map for validation
			case '8': new_y--; break;
			case '2': new_y++; break;
			case '4': new_x--; break;
			case '6': new_x++; break;
			case '5': break; // stay in place
			// END of movement section
			case 'q': return cmd;
		}
		
		bool can_pass = _tiles[new_y][new_x]->get_ispassable();
		if(can_pass){ //don't skip turn if impassable (at least for now[2016-05-11])
			m_y = new_y;
			m_x = new_x;
			return 0;
		}
	}while(cmd != 'q');
	
	return 0;
}