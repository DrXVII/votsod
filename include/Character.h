#ifndef CHARACTER_H
#define CHARACTER_H

#include <ncurses.h>

class Character{
  public:
    Character(int _x, int _y);
    virtual ~Character();

    char GetIcon();
    int GetX();
    int GetY();
    void Act(int _cmd);
    void Print();
  private:
    char Icon;
    int X, Y;
};

#endif // CHARACTER_H
