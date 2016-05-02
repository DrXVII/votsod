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

void Actor::set_y(char _c) {m_y = _c;};

void Actor::set_x(char _c) {m_x = _c;};

void Actor::move(int _cmd)
{
	switch(_cmd){
		case KEY_UP:
			m_y--; break;
		case KEY_DOWN:
			m_y++; break;
		case KEY_LEFT:
			m_x--; break;
		case KEY_RIGHT:
			m_x++; break;
	}
}