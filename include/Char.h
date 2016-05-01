#ifndef CHAR_H
#define CHAR_H

#include <ncurses.h>

class Char{
public:
	Char(int _x, int _y);
	virtual ~Char();

	virtual char get_icon();
	virtual int get_x();
	virtual int get_y();
	virtual void set_y(char _c);
	virtual void set_x(char _c);
	virtual void move(int _cmd);
	virtual int take_turn() = 0;

protected:
	char m_icon;
	int m_x, m_y;
};

#endif // CHAR_H
