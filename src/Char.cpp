#include "Char.h"

Char::Char(int _x, int _y)
{
	m_icon = '@';
	m_x = _x;
	m_y = _y;
}

Char::~Char() {}

char Char::get_icon() {return m_icon;}

int Char::get_x() {return m_x;}

int Char::get_y() {return m_y;}

void Char::set_y(char _c) {m_y = _c;};

void Char::set_x(char _c) {m_x = _c;};

void Char::move(int _cmd)
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