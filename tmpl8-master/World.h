#pragma once

#include "Entity.h"

struct Level
{
public:
	Level(int _mapWidth, int _mapHeight) { m_mapWidth = _mapWidth;  m_mapHeight = _mapHeight; m_mapSize = m_mapWidth * m_mapHeight; };

	// Functions
	int getMapWidth() const { return m_mapWidth; };
	int getMapHeight() const { return m_mapHeight; };
	int getMapSize() const { return m_mapSize; };

	// Varbiables
	UINT8(*mapData)[26];

private:
	// Variables
	int m_mapWidth;
	int m_mapHeight;
	int m_mapSize;
};

class World : public Entity
{
public:
	World();

	// Functions
	void Update(float deltaTime);
	bool PlaceBomb(float2 position);
	bool ExplodeBomb(int2 gridposition);
	static int GetLevelWidth() { return currentLevel->getMapWidth(); };
	UINT8* GetGridPos(float2& pixelPos) const;
	int GetCurrentBlock(float2 position) const;
	UINT8 GetCurrentBlockFromGrid(int2 gridposition) const;
	float2 GetPixelPosFromGrid(int2 gridPosition) const;

	// Variables
	static const int BLOCKSIZE = 16;
	static const int SOFTBLOCKPERCENTAGE = 30;
	static Level* currentLevel;

private:
	// Functions
	virtual void Initialise();
	bool DrawMap();
	bool InitialiseLevels();

	// Variables
	const int m_MARGIN = 32;
	Level* m_level1;
	Surface* m_grass;
	int m_maxBombAmount;
	int m_bombAmount;
	bool m_blocksGenerated;
};