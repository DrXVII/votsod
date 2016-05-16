#include "Tile.h"

Tile::Tile(){m_icon = '!'; m_ispassable = false;}

Tile::~Tile(){}

char Tile::get_icon(){return m_icon;}

void Tile::set_icon(char _icon){m_icon = _icon;}

bool Tile::get_ispassable(){return m_ispassable;}

void Tile::set_ispassable(bool _b){m_ispassable = _b;}
