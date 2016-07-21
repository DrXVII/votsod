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
		//etools::log_add("ERROR: GetTile() Tried to probe a non-existant tile.");
		//string msg = "x:" + to_string(_x) + " y:" + to_string(_y);
		//etools::log_add(msg);
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
		//etools::log_add("ERROR: GetTileIcon() Tried to probe a non-existant tile.");
		//string msg = "x:" + to_string(_x) + " y:" + to_string(_y);
		//etools::log_add(msg);

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
	std::uniform_int_distribution<int> dird(1, 8);
	std::uniform_int_distribution<int> d10(1, 10);
	
	vector<Coord2> rctrs; //room centerpoints
	vector<Coord2> cends; //corridor endpoints
	
	etools::log_add("Genarating level...");
	
	const unsigned rmax = 20;
	for(unsigned i = 0; i < rmax; i++){
		int rm_y = posd(gen); //y of room's upper left corner
		int rm_x = posd(gen); //x of room's upper left corner
		int rm_w = sized(gen); //room's width
		int rm_l = sized(gen); //room's length
		char cor_d = dird(gen); //corridor direction
		
		//for now, only the 4 cardinal numpad direcrtions are allowed - 8, 6, 2, 4
		cor_d = norm_card_dir(cor_d);
		
		//if no rooms are present yet - make the first one before making corridors
		if(rctrs.size() == 0){
			rctrs.push_back(make_room(rm_y, rm_x, rm_w, rm_l));
		}
		else {
			//place corridor from randomly selected room centre if rmax is not reached
			if(i < rmax){
				std::uniform_int_distribution<short> rctrsd(0, rctrs.size() - 1);
				short rcp = rctrsd(gen);
				unsigned cor_y = rctrs[rcp].y;
				unsigned cor_x = rctrs[rcp].x;
				unsigned cor_l = sized(gen);
				
				cends.push_back(make_corr(cor_y, cor_x, cor_l, cor_d));
				
				//winding corridor generation
				unsigned itr1 = 0;
				while(1){
					itr1++;
					//decide if corridor will bend, and generate section if so
					if(d10(gen) >= 6){
						bool cor_corner = true;
						bool backtracking = false;
						char old_cor_d = cor_d;
						cor_y = cends.back().y;
						cor_x = cends.back().x;
						cor_l = sized(gen);
						cor_d = norm_card_dir(dird(gen));
						
						//reroll cor_d if current cor_d would cause backtracking
						switch(cor_d){
							case 2: if(old_cor_d == 8) {backtracking = true;} break;
							case 4: if(old_cor_d == 6) {backtracking = true;} break;
							case 6: if(old_cor_d == 4) {backtracking = true;} break;
							case 8: if(old_cor_d == 2) {backtracking = true;} break;
						}
						if(backtracking){
							char bad_cor_d = cor_d;
							while(cor_d == bad_cor_d){
								cor_d = norm_card_dir(dird(gen));
							}
						}
						
						cends.push_back(make_corr(cor_y, cor_x, cor_l, cor_d, cor_corner));
					}
					else {break;}
					if(itr1 > 10) {etools::log_add("Long loop in lev_gen (corridor)");}
				}
				etools::log_add("corr endpoint: " + to_string(cends.back().y) + "/"
												+ to_string(cends.back().x));
			}
			//allign room placement to the endpoint of most recently created corridor
			rm_x = cends.back().x;
			rm_y = cends.back().y;
			switch(norm_card_dir(cor_d)){
				case 8: rm_y -= (rm_l - 1); rm_x -= (rm_w - 1) / 2; break;
				case 6: rm_y -= (rm_l - 1) / 2; break;
				case 2: rm_x -= (rm_w - 1) / 2; break;
				case 4: rm_x -= (rm_w - 1); rm_y -= (rm_l - 1) / 2; break;
			}
			//out of bounds guards
			if(rm_y < 0 || rm_x < 0) {
				etools::log_add("WARNING: gen_lev() alligned room out of bounds.");
				cends.pop_back(); //removing node that's too close to the border
				if(i > 0) {i--;}
				continue;
			}
			rctrs.push_back(make_room(rm_y, rm_x, rm_w, rm_l));
			//make entrance to new room at the end of most recently created corridor
			place_tile(cends.back().y, cends.back().x, new Tile_Empty);
		}
	}
	etools::log_add("level generated (" + to_string(get_tiles_w())
									+ "/" + to_string(get_tiles_h()) + " )");
}

Coord2 Map::make_room(const unsigned& _y, const unsigned& _x,
										 const unsigned& _w, const unsigned& _l)
{
	string msg = "making room " + to_string(_y) + "/" + to_string(_x)
							 + ":" + to_string(_w) + "/" + to_string(_l);
	etools::log_add(msg);
	
	for(unsigned i = _y; i < _y + _l; i++){
		for(unsigned j = _x; j < _x + _w; j++){
			//if border of room - place wall, else - floor
			if(i == _y || j == _x
			|| i + 1 == _y + _l || j + 1 == _x + _w){
				if(!get_tile(i, j).get_ispassable()){
					place_tile(i, j, new Tile_Wall);
				}
			}
			else {
				place_tile(i, j, new Tile_Empty);
			}
		}
	}
	
	Coord2 roomcenter(_y + (_l / 2), _x + (_w / 2));
	return roomcenter;
}

Coord2 Map::make_corr(unsigned _y, unsigned _x,
											const unsigned& _l, unsigned _dir,
											const bool& _corner)
{
	unsigned left = _l;
	bool end_of_corr = false;

	string msg = "making corr " + to_string(_y) + "/" + to_string(_x)
							 + ":" + to_string(_l) + "-" + to_string(_dir);
	etools::log_add(msg);
	
	if(_l == 0){return Coord2(_y, _x);}
	
	// for now, there are 4 cardinal numpad direcrtions allowed - 8, 6, 2, 4
	_dir = norm_card_dir(_dir);
	
	if(_corner == false){
	//set the real starting point of corridor
		while(get_tile(_y, _x).get_ispassable()){
			switch(_dir){
				case 8: _y--; break;
				case 6: _x++; break;
				case 2: _y++; break;
				case 4: _x--; break;
				default: etools::log_add("ERROR: make_corr: invalid direction argument");
					return Coord2(_y, _x);
			}
			//out of bounds guards
			if(_y == 0 && _dir == 8) {
				etools::log_add("Corr start OOB guard");
				return Coord2(_y, _x);
			}
			if(_x == 0 && _dir == 4) {
				etools::log_add("Corr start OOB guard");
				return Coord2(_y, _x);
			}
		}
	}

	if(_corner){
	// walls around the entry point (to wall corridor corners at bends)
		for(unsigned i = 0; i < 3; i++){
			for(unsigned j = 0; j < 3; j++){
				place_tile_if_empty(_y - 1 + i, _x - 1 + j, new Tile_Wall);
			}
		}
	}
		
	//place corridor on map
	while(left > 0){
		if(end_of_corr){
			place_tile(_y, _x, new Tile_Wall);
		}
		else{
			place_tile(_y, _x, new Tile_Empty);
		}
		left--;
		//place walls if target tile is not passable (e.g. not generated yet)
		if(_dir == 2 || _dir == 8){
			place_tile_if_empty(_y, _x - 1, new Tile_Wall);
			place_tile_if_empty(_y, _x + 1, new Tile_Wall);
		}
		else if(_dir == 4 || _dir == 6){
			place_tile_if_empty(_y - 1, _x, new Tile_Wall);
			place_tile_if_empty(_y + 1, _x, new Tile_Wall);
		}
		
		//cap the end with walls and return when done
		if(end_of_corr){
			return Coord2(_y, _x);
		}
		if(left == 0){
				end_of_corr = true;
		}
		
		switch(_dir){
			case 8: _y--; break;
			case 6: _x++; break;
			case 2: _y++; break;
			case 4: _x--; break;
			default: etools::log_add("ERROR: make_corr: invalid direction argument");
				return Coord2(_y, _x);
		}
		//out of bounds guards (+1 margin for wall placement)
		if(_y < 2 && _dir == 8){
			_y = 1;
			place_tile(_x, _y, new Tile_Wall);
			place_tile(_x + 1, _y, new Tile_Wall);
			place_tile(_x - 1, _y, new Tile_Wall);
			etools::log_add("Corr OOB guard");
			return Coord2(_y, _x);
		}
		if(_x < 2 && _dir == 4){
			_x = 1;
			place_tile(_x, _y, new Tile_Wall);
			place_tile(_x, _y + 1, new Tile_Wall);
			place_tile(_x, _y - 1, new Tile_Wall);
			etools::log_add("Corr OOB guard");
			return Coord2(_y, _x);
		}
	}
	
	// return the endpoint coordinates
	return Coord2(_y, _x);
}

char Map::norm_card_dir(const char& _dir)
{
	char ret = 0;
	
	if(_dir > 6) {ret = 8;}
	else if(_dir > 4 && _dir < 7) {ret = 6;}
	else if(_dir > 2 && _dir < 5) {ret = 4;}
	else {ret = 2;}
	
	return ret;
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
		//etools::log_add("padding row...");//debug
		m_tiles[_y].push_back(new Tile);
		//etools::log_add("row padded ");//debug
	}
	
	//if we are to place the tile just after the end of the row - add the tile
	//etools::log_add("adding at end...");//debug
	if(m_tiles[_y].size() == _x){
		m_tiles[_y].push_back(_tl);
		//etools::log_add("tile placed.");//debug
		if(m_tilemap_w <= _x){//register new map width if the map has expanded
			m_tilemap_w = _x + 1;
		}
		return;
	}
}

void Map::place_tile_if_empty(unsigned const& _y, unsigned const& _x, Tile* _tl)
{	
	if(get_tile(_y, _x).get_ispassable() == false){
		place_tile(_y, _x, _tl);
	}
}

int Map::add_actr(Actor* _a)
{
	if(get_tiles_h() < 1 || get_tiles_w() < 1) {
		etools::log_add("WARNING: can't place actor on empty map.");
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
	
	etools::log_add("Couldn't find a passable tile to place actor!");
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
