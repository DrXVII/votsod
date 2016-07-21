#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <random>

#include <ncurses.h>

#include "etools.h"
#include "Tiles.h"
#include "Actors.h"

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
	unsigned get_tiles_w();
	unsigned get_tiles_h();
	Actor* get_actr(const int& _i);
	Actor* get_actr_atpos(const unsigned int& _y, const unsigned int _x,
												Actor* _exclude);
	int get_actrcount();
	void gen_lev();
	Coord2 make_room(const unsigned& _y, const unsigned& _x,
									 const unsigned& _w, const unsigned& _l);
	Coord2 make_corr(unsigned _y, unsigned _x,
									 const unsigned& _l, unsigned _dir,
									 const bool& = false);
	char norm_card_dir(const char& _dir);//normalise cardinal direction to 2|4|6|8
	void place_tile(unsigned const& _y, unsigned const& _x, Tile* _tl);
	void place_tile_if_empty(unsigned const& _y, unsigned const& _x, Tile* _tl);
	int add_actr(Actor* _a);
	int start_turn();
	void atk(Actor* _att, Actor* _def);
	void remdead();
private:
	unsigned m_tilemap_w;
	vector<vector<Tile*>> m_tiles;
	vector<Actor*> m_actors;
};

#endif // MAP_H
