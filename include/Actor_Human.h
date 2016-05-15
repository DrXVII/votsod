#ifndef ACTOR_HUMAN_H
#define ACTOR_HUMAN_H

#include "Actor.h"

class Actor_Human : public Actor{
public:
	Actor_Human(int _y, int _x);
	~Actor_Human();

	int take_turn(const vector<vector<Tile*>>& _tiles, vector<Actor*>& _actors);
};

#endif // ACTOR_HUMAN_H
