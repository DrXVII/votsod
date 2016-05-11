#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>

#include <ncurses.h>

#include "Tiles.h"
#include "Actor.h"
#include "Actor_Human.h"
#include "Actor_Watcher.h"

using std::vector;
using std::string;
using std::fstream;
using std::to_string;

class Map{
public:
	Map(const string& _filename);
	virtual ~Map();

	bool load_map(const string& _filename);
	Tile get_tile(unsigned int _x, unsigned int _y);
	char get_tile_icon(unsigned int _x, unsigned int _y);
	int get_w();
	int get_h();
	void add_actr(const string& _type, const int& _y, const int& _x);
	Actor* get_actr(const int& _i);
	Actor* get_actr_atpos(const unsigned int& _y, const unsigned int _x,
												Actor* _exclude);
	int get_actrcount();
	int start_turn();
	void move_actor(const int& _cmd, Actor* _act);
	void atk(Actor* _att, Actor* _def);
	void remdead();
private:
	vector<vector<Tile*>> m_tiles;
	vector<Actor*> m_actors;
};

#endif // MAP_H
