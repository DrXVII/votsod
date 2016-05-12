#ifndef ACTOR_WATCHER_H
#define ACTOR_WATCHER_H

#include "Actor.h"

class Actor_Watcher : public Actor{
public:
	Actor_Watcher(int _y, int _x);
	~Actor_Watcher();
	
	int take_turn();
	int take_turn2(const vector<vector<Tile*>>& _tiles, vector<Actor*>& _actors);
private:
};

#endif // ACTOR_WATCHER_H