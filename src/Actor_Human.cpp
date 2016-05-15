#include "Actor_Human.h"

Actor_Human::Actor_Human(int _x, int _y): Actor(_x, _y)
{
	m_icon = '@';
	m_maxhp = 12;
	m_hp = m_maxhp;
	m_dmg = 4;
}

Actor_Human::~Actor_Human() {}

int Actor_Human::take_turn(const vector<vector<Tile*>>& _tiles,
														vector<Actor*>& _actors)
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
		
		// see if destination tile is occupied
		for(size_t i = 0; i < _actors.size(); i++){
			if(_actors[i]->get_y() == new_y && _actors[i]->get_x() == new_x
				&& _actors[i] != this){
				// tile is occupied - can not move there, attacking occupant
				_actors[i]->take_dmg(deal_dmg());
				return 0;
			}
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