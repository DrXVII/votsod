#include "Viewport.h"

Viewport::Viewport(int _y, int _x, int _h, int _w)
{
	m_x = _x;
	m_y = _y;
	m_h = _h;
	m_w = _w;
}

Viewport::~Viewport(){}

void Viewport::print(Map& _m, Char* _c)
{
	for(int i = 0; i < m_w; i++){
		for(int j = 0; j < m_h; j++){
			int offset_y = _c->get_y() - (m_h / 2) + j;
			int offset_x = _c->get_x() - (m_w / 2) + i;
			mvaddch(m_y + j, m_x + i, _m.get_tile_icon(offset_y, offset_x));
		}
	}
	mvaddch(m_y + (m_h / 2), m_x + (m_w / 2), _c->get_icon());
}
