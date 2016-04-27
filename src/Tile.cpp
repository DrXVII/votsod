#include "Tile.h"

Tile::Tile(){
	Icon = '!';
}

Tile::~Tile(){}

char Tile::get_icon(){
	return Icon;
}

void Tile::SetIcon(char _icon){
	Icon = _icon;
}

bool Tile::GetPassable(){
	return Passable;
}

void Tile::SetPassable(bool _b){
	Passable = _b;
}
