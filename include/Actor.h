#ifndef ACTOR_H
#define ACTOR_H

#include <ncurses.h>
#include <string>
#include <vector>

#include "Tile.h"

using std::string;
using std::vector;

//class Tile;

class Actor{
public:
	Actor(const int& _y, const int& _x);
	virtual ~Actor();

	virtual char get_icon();
	virtual unsigned int get_x();
	virtual unsigned int get_y();
	virtual int get_hp();
	virtual void set_y(unsigned const& _i);
	virtual void set_x(unsigned const& _i);
	virtual int move_ai(int _cmd,
											const vector<vector<Tile*>>& _tiles,
											vector<Actor*>& _actors);
	virtual int deal_dmg();
	virtual void take_dmg(int _pts);
	virtual int ai_homming(const vector<vector<Tile*>>& _tiles,
												 vector<Actor*>& _actors);
	virtual int take_turn(const vector<vector<Tile*>>& _tiles,
												 vector<Actor*>& _actors) = 0;

protected:
	char m_icon;
	unsigned int m_x, m_y;
	int m_hp;
	unsigned int m_maxhp;
	unsigned int m_dmg;
};

#endif // ACTOR_H
