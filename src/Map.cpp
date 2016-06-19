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
	
	m_tilemap_w = 0;
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

unsigned Map::get_tiles_w() {return m_tilemap_w;}

unsigned Map::get_tiles_h() {return m_tiles.size();}

void Map::gen_lev()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> posd(0, 99);
	std::uniform_int_distribution<int> sized(4, 10);
	
	//will store room centerpoints for corridor generation
	vector<coord2*> rctrs;
	
//	unsigned rmax = 10;
//	for(unsigned i = 0; i < rmax; i++){
		int rm_y = posd(gen); //y of room's upper left corner
		int rm_x = posd(gen); //x of room's upper left corner
		int rm_w = sized(gen); //room's width
		int rm_l = sized(gen); //room's length
		
		string msg = "making a room " + to_string(rm_x) + "/" + to_string(rm_y) + " ";
		msg = msg + to_string(rm_w) + "/" + to_string(rm_l) + " ... ";
		mvprintw(1, 0, msg.c_str()); refresh();
		make_room(rm_y, rm_x, rm_w, rm_l);
		mvprintw(1, 40, "done."); refresh();
		rctrs.push_back(new coord2);
		// testing with element [0], remove and uncomment before proceeding further
		rctrs[0]->y = rm_y + (rm_l / 2);
		rctrs[0]->x = rm_x + (rm_w / 2);
		make_corr(rctrs[0]->y, rctrs[0]->x, 10, 6);
//		rctrs[i]->y = rm_y + (rm_l / 2);
//		rctrs[i]->x = rm_x + (rm_w / 2);
//	}
}

void Map::make_room(unsigned const& _y, unsigned const& _x,
										unsigned const& _w, unsigned const& _l)
{
	for(unsigned i = _y; i < _y + _l; i++){
		for(unsigned j = _x; j < _x + _w; j++){
			//if border of room - place wall, else - floor
			if(i == _y || j == _x
			|| i + 1 == _y + _l || j + 1 == _x + _w){
				place_tile(i, j, new Tile_Wall);
			}
			else {
				place_tile(i, j, new Tile_Empty);
			}
		}
	}
}

void Map::make_corr(const unsigned int& _y, const unsigned int& _x,
										const unsigned int& _l, const unsigned int& _dir)
{
	//TODO implement out-of-bounds guards
	//TODO implement corridor wall gereration
	
	unsigned left = _l;
	unsigned y = _y;
	unsigned x = _x;
	
	while(get_tile(y, x).get_ispassable()){
		switch(_dir){
			case 8: y--; break;
			case 6: x++; break;
			case 2: y++; break;
			case 4: x--; break;
			default: return;
		}
	}
	
	while(left > 0){
		place_tile(y, x, new Tile_Empty);
		left--;
		switch(_dir){
			case 8: y--; break;
			case 6: x++; break;
			case 2: y++; break;
			case 4: x--; break;
			default: return;
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
	while(m_tiles[_y].size() < _x){
		mvprintw(0,0, "padding row...               ");refresh();//debug
		m_tiles[_y].push_back(new Tile);
		mvprintw(0,40, "row padded ");//debug
		refresh();//debug
	}
	
	//if we are to place the tile just after the end of the row - add the tile
	mvprintw(0,0, "adding at end...            ");//debug
	refresh();//debug
	if(m_tiles[_y].size() == _x){
		m_tiles[_y].push_back(_tl);
		mvprintw(0,40, "tile placed.  ");//debug
		refresh(); //debug
		if(m_tilemap_w <= _x){//register new map width if the map has expanded
			m_tilemap_w = _x + 1;
		}
		return;
	}
}

int Map::add_actr(Actor* _a)
{
	if(get_tiles_h() < 1 || get_tiles_w() < 1) {
		mvprintw(0, 0, "WARNING: can't place actor on empty map.");
		refresh();
		getch();
		return 1;
	}
	
	if(get_tile(_a->get_y(), _a->get_x()).get_ispassable()){
		m_actors.push_back(_a);
		return 0;
	}
	
	// scan around the desired placement coodinates untill a passable tile is
	// found or the scanner wave grows beyond the map's size
	for(unsigned wavefront = 1;
	wavefront <= get_tiles_h() || wavefront <= get_tiles_w();
	wavefront++){
		int a_y = _a->get_y();
		int a_x = _a->get_x();
		
		//scan y coordinates along left and right wavefront borders
		for(int probe_y = a_y - wavefront;
		probe_y <= a_y + int(wavefront);
		probe_y++){
			if(probe_y < 0) {probe_y = 0;}
			if(probe_y >= int(get_tiles_h())) {break;}//beyond bottom of map
		
			int probe_x_left = a_x - wavefront;
			if(probe_x_left < 0) {probe_x_left = 0;}
			if(get_tile(probe_y, probe_x_left).get_ispassable()){
				_a->set_y(probe_y);
				_a->set_x(probe_x_left);
				m_actors.push_back(_a);
				return 0;
			}
			
			unsigned probe_x_right = a_x + wavefront;
			if(probe_x_right >= m_tiles[probe_y].size()) {
				probe_x_right = m_tiles[probe_y].size() - 1;
			}
			if(get_tile(probe_y, probe_x_right).get_ispassable()){
				_a->set_y(probe_y);
				_a->set_x(probe_x_right);
				m_actors.push_back(_a);
				return 0;
			}
		}
		
		//scan x coordinates along top and bottom wavefront borders
		for(int probe_x = a_x - wavefront;
		probe_x <= a_x + int(wavefront);
		probe_x++){
			if(probe_x < 0) {probe_x = 0;}
			if(probe_x >= int(get_tiles_w())) {break;}//beyond rightside end of map
			
			int probe_y_top = a_y - wavefront;
			if(probe_y_top < 0) {probe_y_top = 0;}
			if(get_tile(probe_y_top, probe_x).get_ispassable()){
				_a->set_y(probe_y_top);
				_a->set_x(probe_x);
				m_actors.push_back(_a);
				return 0;
			}
			
			unsigned probe_y_bottom = a_y + wavefront;
			if(probe_y_bottom >= get_tiles_h()){
				probe_y_bottom = get_tiles_h() - 1;
			}
			if(get_tile(probe_y_bottom, probe_x).get_ispassable()){
				_a->set_y(probe_y_bottom);
				_a->set_x(probe_x);
				m_actors.push_back(_a);
				return 0;
			}
		}
	}
	
	mvprintw(0, 0, "Couldn't find a passable tile to place actor!"); refresh();
	return -1;
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
