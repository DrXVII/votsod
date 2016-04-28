#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>

#include <ncurses.h>

#include "Tiles.h"
#include "Char.h"
#include "Char_Human.h"

using namespace std;

class Map{
public:
	Map(const string& _filename);
	virtual ~Map();

	bool load_file(const string& _filename);
	Tile get_tile(int _x, int _y);
	char get_tile_icon(int _x, int _y);
	int get_w();
	int get_h();
	void test_make_char();
	Char* test_get_char();
	int proc_turn();
private:
	vector<vector<Tile*>> m_tiles;
	vector<Char*> m_chars;
};

#endif // MAP_H
