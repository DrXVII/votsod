#include "Char_Human.h"

Char_Human::Char_Human(int _x, int _y): Char(_x, _y){
  Icon = '@';
}

Char_Human::~Char_Human(){
  //dtor
}

int Char_Human::TakeTurn(){
  int cmd = ' ';
  do{
    cmd = getch();
    switch(cmd){
    case KEY_LEFT : /*if(_M.GetTile(Y, X-1).GetPassable())*/ X -= 1; return cmd;
    case KEY_RIGHT: /*if(_M.GetTile(Y, X+1).GetPassable())*/ X += 1; return cmd;
    case KEY_UP   : /*if(_M.GetTile(Y-1, X).GetPassable())*/ Y -= 1; return cmd;
    case KEY_DOWN : /*if(_M.GetTile(Y+1, X).GetPassable())*/ Y += 1; return cmd;
    case 'q': return cmd;
    }
  }while(cmd != 'q');
  return cmd;
}
