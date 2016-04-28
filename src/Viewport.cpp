#include "Viewport.h"

Viewport::Viewport(int _y, int _x, int _h, int _w)
{
	X = _x;
	Y = _y;
	H = _h;
	W = _w;
}

Viewport::~Viewport(){}

void Viewport::Print(Map& _M, Char* _C)
{
	for(int i = 0; i < W; i++){
		for(int j = 0; j < H; j++){
			mvaddch(Y+j, X+i, _M.get_tile_icon(_C->get_y()-(H/2)+j, _C->get_x()-(W/2)+i));
		}
	}
	mvaddch(Y+(H/2), X+(W/2), _C->get_icon());
}
