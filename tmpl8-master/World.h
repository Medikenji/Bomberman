#pragma once

#include "Actor.h"

struct Level
{
	Level(int mapWidth) { this->mapWidth = mapWidth; };
	int *mapData;
	int mapWidth;
	int mapSize;
};

class World : public Actor
{
public:
	World();
	~World();
	bool Tick(float deltaTime);
	int GetType() { return Actor::UNDEFINED; }
	Level* level1;

private:
	Surface* m_grass;
	Surface* m_hardBlock;
	bool DrawMap(Level* currentLevel);
	bool InitialiseLevels();
};



