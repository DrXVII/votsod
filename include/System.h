#ifndef SYSTEM_H
#define SYSTEM_H

#include "Map.h"

class System{
public:
	System();
	~System();
	
	int start_turn(Map& _map);
private:
};

#endif //SYSTEM_H
