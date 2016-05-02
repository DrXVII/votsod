#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Map.h"
#include "Actor.h"

class Viewport{
public:
	Viewport(int _y, int _x, int _h, int _w);
	virtual ~Viewport();

	void print(Map& _M, Actor* _C);
private:
	int m_x, m_y, m_h, m_w, m_centr_x, m_centr_y;
};

#endif // VIEWPORT_H
