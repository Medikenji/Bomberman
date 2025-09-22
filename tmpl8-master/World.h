#pragma once

#include "Entity.h"

struct Level
{
public:
	Level(int _mapWidth, int _mapHeight) { mapWidth = _mapWidth;  mapHeight = _mapHeight; mapSize = mapWidth * mapHeight; };
	UINT8 (*mapData)[50];
	int getMapWidth() { return mapWidth; };
	int getMapHeight() { return mapHeight; };
	int getMapSize() { return mapSize; };
private:
	int mapWidth;
	int mapHeight;
	int mapSize;
};

class World : public Entity
{
public:
	World();
	void Update(float deltaTime);
	void PlaceBomb(float2 position);
	void ExplodeBomb(UINT8* gridposition);
	int GetCurrentBlock(float2 position);
	UINT8 GetCurrentBlockFromGrid(int2 gridposition);
	float2 GetPixelPosFromGrid(int2 gridPosition);
	static Level* currentLevel;
	static int GetLevelWidth() { return currentLevel->getMapWidth(); };
	UINT8* GetGridPos(float2& pixelPos);
	Level* level1;
	static const int BLOCKSIZE = 16;
	static const int SOFTBLOCKPERCENTAGE = 30;

private:
	virtual void Initialise();
	bool DrawMap();
	bool InitialiseLevels();
	//void HandleColl
	const int margin = 32;
	int m_maxBombAmount;
	int m_bombAmount;
	Surface* m_grass;
	bool m_blocksGenerated;
};