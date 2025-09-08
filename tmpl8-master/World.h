#pragma once

#include "Actor.h"

struct Level
{
	Level(int mapWidth) { this->mapWidth = mapWidth; };
	UINT8 *mapData;
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
	int GetCurrentBlock(float x, float y);
	Level* currentLevel;
	Level* level1;

private:
	const int blocksize = 16;
	const int margin = 32;
	Surface* m_grass;
	Surface* m_hardBlock;
	bool DrawMap();
	bool InitialiseLevels();
};



