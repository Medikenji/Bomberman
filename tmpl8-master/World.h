#pragma once

#include "Entity.h"

struct Level
{
	Level(int mapWidth) { this->mapWidth = mapWidth; };
	UINT8 *mapData;
	int mapWidth;
	int mapSize;
};

class World : public Entity
{
public:
	World();
	~World();
	void Update(float deltaTime);
	int GetCurrentBlock(float x, float y);
	Level* currentLevel;
	Level* level1;
	const int blocksize = 16;

private:
	const int margin = 32;
	Surface* m_grass;
	Surface* m_hardBlock;
	bool DrawMap();
	bool InitialiseLevels();
};



