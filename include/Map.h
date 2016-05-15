#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <random>

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
	~Map();

	Tile get_tile(unsigned int _x, unsigned int _y);
	char get_tile_icon(unsigned int _x, unsigned int _y);
	int get_w();
	int get_h();
	Actor* get_actr(const int& _i);
	Actor* get_actr_atpos(const unsigned int& _y, const unsigned int _x,
												Actor* _exclude);
	int get_actrcount();
	void gen_lev();
	void make_room(unsigned const& _y, unsigned const& _x,
								 unsigned const& _w, unsigned const& _l);
	void place_tile(unsigned const& _y, unsigned const& _x, Tile* _tl);
	void add_actr(const string& _type, const int& _y, const int& _x);
	int start_turn();
	void move_actor(const int& _cmd, Actor* _act);
	void atk(Actor* _att, Actor* _def);
	void remdead();
	int gen_rand(int _max, int _min);
private:
	vector<vector<Tile*>> m_tiles;
	vector<Actor*> m_actors;
};

#endif // MAP_H
