#ifndef ACTOR_H
#define ACTOR_H

#include <ncurses.h>

class Actor{
public:
	Actor(const int& _y, const int& _x);
	virtual ~Actor();

	virtual char get_icon();
	virtual unsigned int get_x();
	virtual unsigned int get_y();
	virtual void set_y(char _c);
	virtual void set_x(char _c);
	virtual void move(int _cmd);
	virtual int take_turn() = 0;

protected:
	char m_icon;
	unsigned int m_x, m_y;
};

#endif // CHAR_H
