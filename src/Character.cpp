#include "Character.h"

Character::Character(int _x, int _y){
  Icon = '@';
  X = _x;
  Y = _y;
}

Character::~Character(){
  //dtor
}

char Character::GetIcon(){
  return Icon;
}

int Character::GetX(){
  return X;
}

int Character::GetY(){
  return Y;
}

void Character::Act(int _cmd){
  if(_cmd == KEY_LEFT){
    X -= 1;
  }
  else if(_cmd == KEY_RIGHT || _cmd == 'j'){
    X += 1;
  }
  else if(_cmd == KEY_UP){
    Y -= 1;
  }
  else if(_cmd == KEY_DOWN){
    Y += 1;
  }
  return;
}

void Character::Print(){
  mvaddch(Y, X, Icon);
}
