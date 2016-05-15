#include "Map.h"

#include <string>

Map::Map(const string& _filename)
{
	/*int ln_iter = -1; //iterator to iterate through the x while filling level
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
	file.close();*/
	gen_lev();
}

//TODO eliminate memleaks
Map::~Map(){}

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

void Map::gen_lev()
{
	//TODO - implement the "random" in random room generation
	/*int rm_cny = gen_rand(0, 100); //y of the rooms center
	int rm_cnx = gen_rand(0, 100); //x of the rooms center
	int rm_w = gen_rand(2, 20);
	int rm_l = gen_rand(2, 20);
	
	make_room(rm_cny, rm_cnx, rm_w, rm_l);*/
	
	make_room(0, 0, 10, 10);
}

void Map::make_room(unsigned const& _y, unsigned const& _x,
										unsigned const& _w, unsigned const& _l)
{
	for(unsigned i = _y; i < _y + _l; i++){
		for(unsigned j = _x; j < _x + _w; j++){
			place_tile(i, j, new Tile_Empty);
		}
	}
}

void Map::place_tile(unsigned const& _y, unsigned const& _x, Tile* _tl)
{
	// while the map is too short - add rows
	while(m_tiles.size() <= _y){
		
		vector<Tile*> first_dim;
		m_tiles.push_back(first_dim);
	}
	// if a tile is already at our coordinates - replace it; job's done.
	if(m_tiles[_y].size() > _x){
		delete m_tiles[_y][_x];
		m_tiles[_y][_x] = _tl;
		return;
	}
	
	//while the row is too short to place our tile just after it's end - extend
	mvprintw(0,0, "padding row               ");//debug
	refresh();//debug
	while(m_tiles[_y].size() < _x){
		m_tiles[_y].push_back(new Tile);
	}
	mvprintw(1,0, "row padded               ");//debug
	refresh();//debug
	
	//if we are to place the tile just after the end of the row - add the tile
	mvprintw(2,0, "adding at end               ");//debug
	refresh();//debug
	if(m_tiles[_y].size() == _x){
		m_tiles[_y].push_back(_tl);
		mvprintw(3,0, "tile placed               ");//debug
		refresh(); //debug
		return;
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

int Map::start_turn()
{
	int cmd = 0;
	for(size_t i = 0; i < m_actors.size(); i++){
		cmd = m_actors[i]->take_turn(m_tiles, m_actors);
		remdead();

		if(cmd == 'q'){
			return cmd;
		}
	}
	return cmd;
}

void Map::atk(Actor* _att, Actor* _def)
{
	_def->take_dmg(_att->deal_dmg());
}

void Map::remdead()
{
	/*TODO consider storing the m_actors array iterator in actor object as m_ID
	 * in order to access actors more efficiently for operations as this */
	
	//if the hero is dead ( actor(0) ),- end game
	if(m_actors[0]->get_hp() <= 0){
		return;
	}
	
	for(size_t i = 1; i < m_actors.size(); i++){
		if(m_actors[i]->get_hp() <= 0){
			m_actors.erase(m_actors.begin() + i);
		}
	}
}

int Map::gen_rand(int _min, int _max)
{
	std::default_random_engine gen(time(NULL));
	std::uniform_int_distribution<int> distr(_min, _max);
	
	return distr(gen);
}
