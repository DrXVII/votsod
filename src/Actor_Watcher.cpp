#include "Actor_Watcher.h"

Actor_Watcher::Actor_Watcher(int _y, int _x): Actor(_y, _x)
{
	m_icon = 'w';
}

Actor_Watcher::~Actor_Watcher() {}

int Actor_Watcher::take_turn() {return 0;}