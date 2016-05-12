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

std::string Actor::get_controller() {return m_controller;}

void Actor::set_y(char _c) {m_y = _c;};

void Actor::set_x(char _c) {m_x = _c;};

void Actor::move(int _cmd)
{
	switch(_cmd){
		case '8':
			m_y--; break;
		case '2':
			m_y++; break;
		case '4':
			m_x--; break;
		case '6':
			m_x++; break;
		case '5':
			//stay in place
			break;
	}
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
												 Actor* _tgt)
{
	unsigned int tgt_y = _tgt->get_y();
	unsigned int tgt_x = _tgt->get_x();
	
	if(m_y > tgt_y) {return '8';}
	else if(m_y < tgt_y) {return '2';}
	else if(m_x > tgt_x) {return '4';}
	else if(m_x < tgt_x) {return '6';}
	else {return '5';}
}
