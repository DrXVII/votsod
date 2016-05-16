#include "Actor.h"

Actor::Actor(const int& _y, const int& _x)
{
	m_icon = '@';
	m_x = _x;
	m_y = _y;
}

Actor::~Actor() {}

char Actor::get_icon() {return m_icon;}

unsigned int Actor::get_x() {return m_x;}

unsigned int Actor::get_y() {return m_y;}

int Actor::get_hp() {return m_hp;}

void Actor::set_y(unsigned const& _i) {m_y = _i;};

void Actor::set_x(unsigned const& _i) {m_x = _i;};

int Actor::move_ai(int _cmd,
									 const vector<vector<Tile*>>& _tiles,
									 vector<Actor*>& _actors)
{
	unsigned int new_y;
	unsigned int new_x;
	
	new_y = m_y;
	new_x = m_x;
	
	switch(_cmd){
		case '8': new_y--; break;
		case '2': new_y++; break;
		case '4': new_x--; break;
		case '6': new_x++; break;
		case '5': break; //stay in place
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
	
	return 1; //indicates, that the turn has not been spent yet (did nothing)
}

int Actor::deal_dmg()
{
	//advanecd attack calculations and special attacks will be added later
	return m_dmg;
}

void Actor::take_dmg(int _pts)
{
	if(m_hp > _pts){
		m_hp -= _pts;
	}
	else{
		m_hp = 0;
	}
}

int Actor::ai_homming(const vector<vector<Tile*>>& _tiles,
												 vector<Actor*>& _actors)
{
	int trnsleft = 1; // 0 - turn spent
	unsigned int tgt_y = _actors[0]->get_y();
	unsigned int tgt_x = _actors[0]->get_x();
	
	do{
		if(m_y > tgt_y) {trnsleft = move_ai('8', _tiles, _actors);}
		if(m_y < tgt_y) {trnsleft = move_ai('2', _tiles, _actors);}
		if(m_x > tgt_x && trnsleft > 0) {trnsleft = move_ai('4', _tiles, _actors);}
		if(m_x < tgt_x && trnsleft > 0) {trnsleft = move_ai('6', _tiles, _actors);}
		if(trnsleft > 0) {trnsleft = move_ai('5', _tiles, _actors);}
		trnsleft = 0;
	}while(trnsleft == 1);
	return 0;
}
