#pragma once
#include "Entity.h"

class EntityContainer;
class BomberMan;

struct EnemyList {
	EnemyList(uint_fast8_t _ballom, uint_fast8_t _dahl) : ballom_amount(_ballom), dahl_amount(_dahl) {};
	uint_fast8_t ballom_amount = 0;
	uint_fast8_t dahl_amount = 0;
};

struct Level
{
public:
	// Varbiables
	static const int MAP_WIDTH = 25;
	static const int MAP_HEIGHT = 13;
	static const int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT;
	uint_fast8_t mapData[MAP_HEIGHT][MAP_WIDTH] = {
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
	void AddScore(uint_fast16_t _score) { m_score += _score; };
	void PlaceBomb(float2 _position, BomberMan* _bomberMan);
	void ExplodeBomb(uint2 _gridPosition, uint_fast8_t _explosionSize);
	bool AllowNextLevel();
	uint2 GetGridPos(float2 _pixelPosition) const;
	uint_fast8_t GetCurrentBlock(float2 _pixelPosition) const;
	uint_fast8_t GetCurrentBlockFromGrid(uint2 _gridPosition) const;
	float2 GetPixelPosFromGrid(uint2 _gridPosition) const;

	// Variables
	static const int BLOCKSIZE = 16;
	static const int SOFTBLOCKPERCENTAGE = 25;

private:
	// Functions
	void Update(float _deltaTime);
	virtual void Initialize();
	void DrawMap();
	void GenerateMap();
	void GenerateInteractables();
	Entity* AddKillableEntity(Entity* _entity);

	// Variables
	static const int MARGIN = 32;
	inline static uint_fast16_t score = 0;
	Entity* m_killableEntities[32] = { nullptr };
	int m_killableEntitiesAmount;
	uint_fast16_t m_score;
	Level* m_level;
	EnemyList* m_enemyList = nullptr;

	// Template shenanigans

	// Sander helped me explain how templates work

	template<class T>
	void generateEnemies(int _enemyAmount) {
		for (int i = 0; i < _enemyAmount; i++)
		{
			bool possibleSpawn = false;
			uint2 spawnPosition = { NULL };
			while (!possibleSpawn)
			{
				int randomX = (rand() % (m_level->MAP_WIDTH - 5)) + 5;
				int randomY = (rand() % (m_level->MAP_HEIGHT - 5)) + 5;
				if (GetCurrentBlockFromGrid({ randomX, randomY }) == Block::GRASS)
				{
					spawnPosition = { randomX, randomY };
					possibleSpawn = true;
				}
			}
			float2 setposition = GetPixelPosFromGrid(spawnPosition);
			Entity* enemy = static_cast<Entity*>(new T());
			enemy->position = setposition;
			m_container->AddEntity(AddKillableEntity(enemy));
		}
	}
};