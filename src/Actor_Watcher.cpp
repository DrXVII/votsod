#include "Actor_Watcher.h"

Actor_Watcher::Actor_Watcher(int _y, int _x): Actor(_y, _x)
{
	m_controller = "AI_HOMMING";
	m_icon = 'w';
	m_maxhp = 5;
	m_hp = m_maxhp;
	m_dmg = 1;
}

Actor_Watcher::~Actor_Watcher() {}

int Actor_Watcher::take_turn() {return 0;}

int Actor_Watcher::take_turn2(const vector<vector<Tile*>>& _tiles) {return 0;}