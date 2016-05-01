#include "Map.h"

#include <string>

Map::Map(const string& _filename)
{
	int ln_iter = -1; //iterator to iterate through the x while filling level
	fstream file; //level file stream
	string line; //the string to be filled with getline();
	vector<Tile*> v1;//empty tile vector to fill the first dimension of m_tiles;

	file.open(_filename, fstream::in | fstream::binary);
	if(file.fail()){
		mvprintw(5, 10, "Error while opening level file!");
		getch();
	}

	do{
		getline(file, line);
		if(!file.eof()){
			m_tiles.push_back(v1);
			ln_iter += 1;
			for(int i = 0; i < line.size(); i++){
				switch(line[i]){
				case '.':
					m_tiles[ln_iter].push_back(new Tile_Empty);
					break;
				case '#':
					m_tiles[ln_iter].push_back(new Tile_Wall);
					break;
				default:
					m_tiles[ln_iter].push_back(new Tile);
				}
			}
		}
		else{
			mvprintw(23, 0, "Level built.");
		}
	}while(!file.eof());
	file.close();
}

//TODO destroy m_tiles
Map::~Map(){}

bool Map::load_map(const string& _filename)
{
	/*TODO figure out what is throwing the 'illegal instruction' error in this
	function and remove the duplicate logic from the consturctor.
	Don't forget to handle the error thrown in calling code */
	int ln_iter = -1; //iterator to iterate through the x while filling level
	fstream file; //level file stream
	string line; //the string to be filled with getline();
	vector<Tile*> v1;//empty tile vector to fill the first dimension of m_tiles;

	file.open(_filename, fstream::in | fstream::binary);
	if(file.fail()){
		mvprintw(5, 10, "Error while opening level file!");
		getch();
		return 1;
	}

	do{
		getline(file, line);
		if(!file.eof()){
			m_tiles.push_back(v1);
			ln_iter += 1;
			for(int i = 0; i < line.size(); i++){
				switch(line[i]){
				case '.':
					m_tiles[ln_iter].push_back(new Tile_Empty);
					break;
				case '#':
					m_tiles[ln_iter].push_back(new Tile_Wall);
					break;
				default:
					m_tiles[ln_iter].push_back(new Tile);
				}
			}
		}
		else{
			mvprintw(23, 0, "Level built.");
		}
	}while(!file.eof());
	file.close();
}

Tile Map::get_tile(int _y, int _x)
{
	if(_y < m_tiles.size() && _x < m_tiles[_y].size()){
		return *m_tiles[_y][_x];
	}
	else{
		mvprintw(20, 0, "ERROR: GetTile() Tried to probe a non-existant tile.");
		string sX = to_string(_x);
		string sY = to_string(_y);
		string sB = "x:" + sX + " y:" + sY;
		mvprintw(21, 0, sB.c_str());
		Tile emptyTile;
		return emptyTile;
	}
}

char Map::get_tile_icon(int _y, int _x)
{
	if(_y < m_tiles.size() && _x < m_tiles[_y].size()){
		char ret = 0;
		ret = m_tiles[_y][_x]->get_icon();
		if(ret == 0 || ret == ' '){
			return '0';
		}
		return ret;
	}
	else{
		mvprintw(20, 0, "ERROR: GetTileIcon() Tried to probe a non-existant tile.");
		string sX = to_string(_x);
		string sY = to_string(_y);
		string sB = "x:" + sX + " y:" + sY;
		mvprintw(21, 0, sB.c_str());

		return '!';
	}
}

void Map::test_make_char()
{
	m_chars.push_back(new Char_Human(40, 10));
}

Char* Map::get_actr(const int& _i) {return m_chars[_i];}

int Map::get_actrcount() {return m_chars.size();}

int Map::get_w()
{
	return m_tiles.size();
}

int Map::get_h()
{
	return m_tiles[0].size();
}

int Map::start_turn()
{
	int ret = ' ';
	for(int i = 0; i < m_chars.size(); i++){
		ret = m_chars[i]->take_turn();
		move_actor(ret, m_chars[i]);
		if(ret == 'q'){
			return ret;
		}
	}
	return ret;
}

void Map::move_actor(const int& _cmd, Char* _act)
{
	int old_y = _act->get_y();
	int old_x = _act->get_x();
	
	_act->move(_cmd);
	
	int new_y = _act->get_y();
	int new_x = _act->get_x();
	bool can_pass = m_tiles[new_y][new_x]->get_ispassable();
	
	if(!can_pass){
		//if can't pass here - place the actor back
		_act->set_y(old_y);
		_act->set_x(old_x);
	}
}

