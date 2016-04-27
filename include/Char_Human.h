#ifndef CHAR_HUMAN_H
#define CHAR_HUMAN_H

#include <Char.h>


class Char_Human : public Char{
	public:
		Char_Human(int _x, int _y);
		virtual ~Char_Human();

		int take_turn();
};

#endif // CHAR_HUMAN_H
