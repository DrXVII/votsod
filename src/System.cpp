#include "System.h"

#include "Map.h"

System::System(){}

System::~System(){}

int System::start_turn(Map& _map)
{
	_map.start_turn();
}
