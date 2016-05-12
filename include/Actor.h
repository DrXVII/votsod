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
	virtual string get_controller();
	virtual void set_y(char _c);
	virtual void set_x(char _c);
	virtual void move(int _cmd);
	virtual int deal_dmg();
	virtual void take_dmg(int _pts);
	virtual int ai_homming(const vector<vector<Tile*>>& _tiles,
												 Actor* _tgt);
	virtual int take_turn() = 0;
	virtual int take_turn2(const vector<vector<Tile*>>& _tiles,
												 vector<Actor*>& _actors) = 0;

protected:
	string m_controller;
	char m_icon;
	unsigned int m_x, m_y;
	int m_hp;
	unsigned int m_maxhp;
	unsigned int m_dmg;
};

#endif // ACTOR_H
