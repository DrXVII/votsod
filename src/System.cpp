#include "System.h"

System::System(){}

System::~System(){}

Map* System::get_currmap() {return m_currmap;}
int System::get_herohp() {return m_currmap->get_actr(0)->get_hp();}

void System::init()
{
	m_maps.push_back(new Map("tstTxt"));
	m_currmap = m_maps[0];
	m_main_view = new Viewport(0, 0, 19, 61);
}

int System::start_turn()
{
	return m_currmap->start_turn();
}

void System::render_mainw()
{
	string sbuf;
		
	clear();
	m_main_view->print(m_currmap, m_currmap->get_actr(0)); //actor 0 is our main character
	sbuf = "HP: " + to_string(m_currmap->get_actr(0)->get_hp());
	mvprintw(0, 63, sbuf.c_str());
	sbuf = "DEBUG: x: " + to_string(m_currmap->get_actr(0)->get_x());
	sbuf = sbuf + " y:" + to_string(m_currmap->get_actr(0)->get_y());
	mvprintw(23, 0, sbuf.c_str());
	refresh();
}

void System::add_actr(Actor* _a)
{
	m_currmap->add_actr(_a);
}
