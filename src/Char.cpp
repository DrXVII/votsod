#include "Char.h"

Char::Char(int _x, int _y){
  Icon = '@';
  X = _x;
  Y = _y;
}

Char::~Char(){
  //dtor
}

char Char::GetIcon(){
  return Icon;
}

int Char::GetX(){
  return X;
}

int Char::GetY(){
  return Y;
}
