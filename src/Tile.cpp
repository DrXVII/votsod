#include "Tile.h"

Tile::Tile(){
  Icon = '!';
}

Tile::~Tile(){}

char Tile::GetIcon(){
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
