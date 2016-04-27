#include "System.h"

#include "Map.h"

System::System(){}

System::~System(){}

int System::startTurn(Map& _map)
{
	_map.NextTurn();
}
