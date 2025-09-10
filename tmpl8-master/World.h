#pragma once

#include "Entity.h"
#include "HardBlock.h"

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
	static Level* currentLevel;
	static int GetLevelWidth() { return currentLevel->mapWidth; };
	Level* level1;
	static const int BLOCKSIZE = 16;

private:
	const int margin = 32;
	Surface* m_grass;
	bool m_hardBlocksGenerated;
	bool DrawMap();
	bool InitialiseLevels();
};



