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
			for(size_t i = 0; i < line.size(); i++){
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
			for(size_t i = 0; i < line.size(); i++){
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
	return 0;
}

Tile Map::get_tile(unsigned int _y, unsigned int _x)
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

char Map::get_tile_icon(unsigned int _y, unsigned int _x)
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

void Map::add_actr(const string& _type, const int& _y, const int& _x)
{
	if(_type == "human"){
		m_actors.push_back(new Actor_Human(_y, _x));
	}
	else if(_type == "watcher"){
		m_actors.push_back(new Actor_Watcher(_y, _x));
	}
	else{
		mvprintw(22, 0, "WARNING: Rquest for unexpected actor type");
		getch();
	}
}

Actor* Map::get_actr(const int& _i) {return m_actors[_i];}

Actor* Map::get_actr_atpos(const unsigned int& _y, const unsigned int _x,
													 Actor*	_exclude)
{
	for(size_t i = 0; i < m_actors.size(); i++){
		if(m_actors[i]->get_y() == _y && m_actors[i]->get_x() == _x
			 && m_actors[i] != _exclude){
			
			return m_actors[i];
		}
	}
	
	return NULL;
}

int Map::get_actrcount() {return m_actors.size();}

int Map::get_w() {return m_tiles.size();}

int Map::get_h() {return m_tiles[0].size();}

int Map::start_turn()
{
	int ret = ' ';
	for(size_t i = 0; i < m_actors.size(); i++){
		ret = m_actors[i]->take_turn();
		move_actor(ret, m_actors[i]);
		if(ret == 'q'){
			return ret;
		}
	}
	return ret;
}

void Map::move_actor(const int& _cmd, Actor* _act)
{
	unsigned int old_y = _act->get_y();
	unsigned int old_x = _act->get_x();
	
	_act->move(_cmd);
	
	unsigned int new_y = _act->get_y();
	unsigned int new_x = _act->get_x();
	bool can_pass = m_tiles[new_y][new_x]->get_ispassable();
	bool tile_ocpd = (get_actr_atpos(new_y, new_x, _act) == NULL) ? false : true;
	
	if(!can_pass){
		//if can't pass here - place the actor back
		_act->set_y(old_y);
		_act->set_x(old_x);
	}
	if(tile_ocpd){
		//somebody(thing) is on the tile, place actor back
		_act->set_y(old_y);
		_act->set_x(old_x);
		mvprintw(22, 0, "Tile occupied!");
		refresh();
		//and initiate combat
		//... TODO replace with combat function call
	}
}
