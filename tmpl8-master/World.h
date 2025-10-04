#pragma once
#include "Entity.h"

class EntityContainer;

struct Level
{
public:
	// Functions
	int GetMapWidth() const { return m_mapWidth; };
	int GetMapHeight() const { return m_mapHeight; };
	int GetMapSize() const { return m_mapSize; };

	// Varbiables
	UINT8 mapData[13][25] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

private:
	// Variables
	const int m_mapWidth = 25;
	const int m_mapHeight = 13;
	const int m_mapSize = m_mapWidth * m_mapHeight;
};

class World : public Entity
{
public:
	World();

	// Enums
	enum Block{
		HARDWALL = 1,
		GRASS = 2,
		SOFTWALL = 3,
		BOMB = 4
	};


	// Functions
	void Update(float _deltaTime);
	bool PlaceBomb(float2 _position);
	bool ExplodeBomb(uint2 _gridPosition);
	static Level GetLevel() { return m_level; };
	uint2 GetGridPos(float2 _pixelPosition) const;
	UINT8 GetCurrentBlock(float2 _pixelPosition) const;
	UINT8 GetCurrentBlockFromGrid(uint2 _gridPosition) const;
	float2 GetPixelPosFromGrid(uint2 _gridPosition) const;

	// Variables
	static const int BLOCKSIZE = 16;
	static const int SOFTBLOCKPERCENTAGE = 30;

private:
	// Functions
	virtual void Initialise();
	bool DrawMap();
	bool GenerateMap();

	// Variables
	const int m_MARGIN = 32;
	Surface* m_grass;
	static Level m_level;
	int m_maxBombAmount;
	int m_bombAmount;
};