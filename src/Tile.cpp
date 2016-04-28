#include "Tile.h"

Tile::Tile(){Icon = '!';}

Tile::~Tile(){}

char Tile::get_icon(){return Icon;}

void Tile::set_icon(char _icon){Icon = _icon;}

bool Tile::get_ispassable(){return m_ispassable;}

void Tile::set_ispassable(bool _b){m_ispassable = _b;}
