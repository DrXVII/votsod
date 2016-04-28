#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Map.h"
#include "Char.h"

class Viewport{
public:
	Viewport(int _y, int _x, int _h, int _w);
	virtual ~Viewport();

	void print(Map& _M, Char* _C);
private:
	int m_x, m_y, m_h, m_w;
};

#endif // VIEWPORT_H
