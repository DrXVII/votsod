#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Map.h"
#include "Char.h"

class Viewport
{
	public:
		Viewport(int _y, int _x, int _h, int _w);
		virtual ~Viewport();

		void Print(Map& _M, Char* _C);
	protected:
	private:
	int X, Y, H, W;
};

#endif // VIEWPORT_H
