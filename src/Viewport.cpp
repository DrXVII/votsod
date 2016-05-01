#include "Viewport.h"

Viewport::Viewport(int _y, int _x, int _h, int _w)
{
	m_x = _x;
	m_y = _y;
	m_h = _h;
	m_w = _w;
	m_centr_x = m_x + (m_w / 2);
	m_centr_y = m_y + (m_h / 2);
}

Viewport::~Viewport(){}

void Viewport::print(Map& _m, Char* _c)
{
	int camcenter_y = _c->get_y();
	int camcenter_x = _c->get_x();
	
	for(int i = 0; i < m_w; i++){
		for(int j = 0; j < m_h; j++){
			int offset_y = camcenter_y - (m_h / 2) + j;
			int offset_x = camcenter_x - (m_w / 2) + i;
			mvaddch(m_y + j, m_x + i, _m.get_tile_icon(offset_y, offset_x));
		}
	}
	
	for(int i = 0; i < _m.get_actrcount(); i++){
		int actdist_y = _m.get_actr(i)->get_y() - camcenter_y;
		int actdist_x = _m.get_actr(i)->get_x() - camcenter_x;
		
		if(std::abs(actdist_y) < (m_h / 2) && std::abs(actdist_x) < (m_w / 2)){
			char act_icon = _m.get_actr(i)->get_icon();
			mvaddch(m_centr_y + actdist_y, m_centr_x + actdist_x, _c->get_icon());
		}
	}
}
