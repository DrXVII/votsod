#ifndef SYSTEM_H
#define SYSTEM_H

#include "Map.h"
#include "Viewport.h"

class System{
public:
	System();
	~System();
	
	Map* get_currmap();
	int get_herohp();
	void init();
	int start_turn();
	void render_mainw();
	void add_actr(Actor* _a);
private:
	vector<Map*> m_maps;
	Map* m_currmap;
	Viewport* m_main_view;
};

#endif //SYSTEM_H
