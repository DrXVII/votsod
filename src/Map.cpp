#include "Map.h"

Map::Map(string _mapFile){

  int lineItr = -1; //iterator to iterate through the x while filling level
  fstream file; //level file stream
  string line; //the string to be filled with getline();
  vector<Tile*> v1;//empty tile vector to fill the first dimension of Vtiles;

  file.open(_mapFile, fstream::in | fstream::binary);
  if(file.fail()){
    mvprintw(5, 10, "Error while opening level file!");
    getch();
  }

  do{
    getline(file, line);
    if(!file.eof()){
      Vtiles.push_back(v1);
      lineItr += 1;
      for(int i = 0; i < line.size(); i++){
        switch(line[i]){
        case '.':
          Vtiles[lineItr].push_back(new Tile_Empty);
          break;
        case '#':
          Vtiles[lineItr].push_back(new Tile_Wall);
          break;
        default:
          Vtiles[lineItr].push_back(new Tile);
        }
      }
    }
    else{
      mvprintw(23, 0, "Level built.");
    }
  }while(!file.eof());
  file.close();
}

//TODO destroy Vtiles
Map::~Map(){}

Tile Map::GetTile(int _y, int _x){
  if(_y < Vtiles.size() && _x < Vtiles[_y].size()){
    return *Vtiles[_y][_x];
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

char Map::GetTileIcon(int _y, int _x){
  if(_y < Vtiles.size() && _x < Vtiles[_y].size()){
    char ret = 0;
    ret = Vtiles[_y][_x]->GetIcon();
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

void Map::test_make_char(){
  m_vChars.push_back(new Char_Human(40, 10));
}

Char* Map::test_get_char(){
  return m_vChars[0];
}
//TODO - consider moving such functionality into a System class
int Map::NextTurn(){
  int ret = ' ';
  for(int i = 0; i < m_vChars.size(); i++){
    ret = m_vChars[i]->TakeTurn();
    if(ret == 'q'){
      return ret;
    }
  }
  return ret;
}

int Map::GetTilemapW(){
  return Vtiles.size();
}

int Map::GetTilemapH(){
  return Vtiles[0].size();
}
