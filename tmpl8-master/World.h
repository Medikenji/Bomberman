#pragma once
#include "Entity.h"

class EntityContainer;

struct EnemyList {
	EnemyList(UINT8 _ballom, UINT8 _dahl) : ballom_amount(_ballom), dahl_amount(_dahl) {};
	UINT8 ballom_amount = 0;
	UINT8 dahl_amount = 0;
};

struct Level
{
public:
	// Varbiables
	static const int MAP_WIDTH = 25;
	static const int MAP_HEIGHT = 13;
	static const int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT;
	UINT8 mapData[MAP_HEIGHT][MAP_WIDTH] = {
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
};

class World : public Entity
{
public:
	World(EnemyList* _list);
	~World();

	// Enums
	enum Block {
		HARDWALL = 1,
		GRASS = 2,
		SOFTWALL = 3,
		BOMB = 4
	};

	// Functions
	bool PlaceBomb(float2 _position);
	bool ExplodeBomb(uint2 _gridPosition);
	uint2 GetGridPos(float2 _pixelPosition) const;
	UINT8 GetCurrentBlock(float2 _pixelPosition) const;
	UINT8 GetCurrentBlockFromGrid(uint2 _gridPosition) const;
	float2 GetPixelPosFromGrid(uint2 _gridPosition) const;

	// Variables
	static const int BLOCKSIZE = 16;
	static const int SOFTBLOCKPERCENTAGE = 30;

private:
	// Functions
	void Update(float _deltaTime);
	virtual void Initialize();
	bool DrawMap();
	bool GenerateMap();
	Entity* AddKillableEntity(Entity* _entity);

	// Variables
	static const int MARGIN = 32;
	Entity* m_killableEntities[32] = { nullptr };
	int m_killableEntitiesAmount;
	Surface* m_grass;
	Level* m_level;
	EnemyList* m_enemyList = nullptr;
	int m_maxBombAmount;
	int m_bombAmount;
};