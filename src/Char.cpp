#include "Char.h"

Char::Char(int _x, int _y)
{
	m_icon = '@';
	m_x = _x;
	m_y = _y;
}

Char::~Char()
{
	//dtor
}

char Char::get_icon()
{
	return m_icon;
}

int Char::get_x()
{
	return m_x;
}

int Char::get_y()
{
	return m_y;
}
