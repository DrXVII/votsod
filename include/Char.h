#ifndef CHAR_H
#define CHAR_H

#include <ncurses.h>

class Char{
  public:
    Char(int _x, int _y);
    virtual ~Char();

    virtual char GetIcon();
    virtual int GetX();
    virtual int GetY();

    virtual int TakeTurn() = 0;



    char Icon;
    int X, Y;
};

#endif // CHAR_H
