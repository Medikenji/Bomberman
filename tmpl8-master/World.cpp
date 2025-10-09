#include "precomp.h"
#include "World.h"
#include "AudioManager.h"
#include "HardBlock.h"
#include "SoftBlock.h"
#include "BomberMan.h"
#include "Bomb.h"
#include "Ballom.h"


World::World(EnemyList* _list) {
	srand((unsigned int)time(0));
	m_enemyList = _list;
	m_killableEntitiesAmount = 0;
	m_maxBombAmount = 1;
	m_bombAmount = 0;
	position.y = 32;
	m_level = new Level();
	m_grass = new Surface("assets/Grass.png");
}


World::~World()
{
	delete m_level;
	delete m_grass;
	delete m_enemyList;
}


void World::Initialize()
{
	for (int i = 0; i < BomberMan::GetPlayerAmount(); i++)
	{
		container->AddEntity(AddKillableEntity(BomberMan::GetPlayers()[i]));
	}
	GenerateMap();
	AudioManager::GetAudioManager()->PlayAudio(Audio::MainTheme);
}


void World::Update(float)
{
	DrawMap();
}


bool World::PlaceBomb(float2 _position)
{
	if (m_bombAmount < m_maxBombAmount)
	{
		uint2 intGridPos = GetGridPos(_position);
		UINT8 gridPos[2] = { (UINT8)intGridPos.x, (UINT8)intGridPos.y };
		if (m_level->mapData[gridPos[1]][gridPos[0]] != Block::GRASS)
			return true;

		m_level->mapData[gridPos[1]][gridPos[0]] = Block::BOMB;
		container->AddEntity(new Bomb(GetPixelPosFromGrid({ gridPos[0], gridPos[1] })));
		m_bombAmount++;
	}
	return true;
}


bool World::ExplodeBomb(uint2 _gridPosition)
{
	const int DIRX[4] = { -1, 0, 1, 0 };
	const int DIRY[4] = { 0, -1, 0, 1 };

	UINT8 explosionSize = 1;
	UINT8 bombPos[2] = { (UINT8)_gridPosition.x,(UINT8)_gridPosition.y };
	float2 bombPixelPos = GetPixelPosFromGrid({ (int)_gridPosition.x,(int)_gridPosition.y });

	container->AddEntity(new BombExplosion(bombPixelPos, BombExplosion::MIDDLE, m_killableEntities, m_killableEntitiesAmount));
	for (int d = 0; d < 4; ++d)
	{
		// Check sides for blocks to break
		for (UINT8 i = 1; i <= explosionSize; ++i)
		{
			int x = bombPos[0] + DIRX[d] * i;
			int y = bombPos[1] + DIRY[d] * i;
			bombPixelPos = GetPixelPosFromGrid({ x,y });
			UINT8& cell = m_level->mapData[y][x];
			if (cell == Block::HARDWALL) break;
			if (cell == Block::SOFTWALL)
			{
				cell = Block::GRASS;
				break;
			}

			// Magic numbers that coincidentally fit with the animation
			const int side = (2 + 2 * d);
			// Spawn in explosion
			if (i == explosionSize)
			{
				container->AddEntity(new BombExplosion(bombPixelPos, side - 1, m_killableEntities, m_killableEntitiesAmount));
				break;
			}
			container->AddEntity(new BombExplosion(bombPixelPos, side, m_killableEntities, m_killableEntitiesAmount));
		}
	}

	m_level->mapData[bombPos[1]][bombPos[0]] = Block::GRASS;
	m_bombAmount--;
	return true;
}


bool World::DrawMap()
{
	for (int j = 0; j < m_level->MAP_HEIGHT; j++)
	{
		for (int i = 0; i < m_level->MAP_WIDTH; i++)
		{
			const float x = (float)(i * BLOCKSIZE) + position.x;
			const float y = (float)(j * BLOCKSIZE) + position.y;
			float2 drawPosition = { x,y };
			if (m_level->mapData[j][i] == Block::GRASS || m_level->mapData[j][i] == Block::BOMB)
			{
				container->CopyToSurfaces(m_grass, drawPosition);
			}
		}
	}
	return true;
}


bool World::GenerateMap()
{
	for (int j = 0; j < m_level->MAP_HEIGHT; j++)
	{
		for (int i = 0; i < m_level->MAP_WIDTH; i++)
		{
			const float x = (float)(i * BLOCKSIZE) + position.x;
			const float y = (float)(j * BLOCKSIZE) + position.y;
			float2 drawPosition = { x,y };
			if (m_level->mapData[j][i] == 2)
			{
				if (rand() % 100 < SOFTBLOCKPERCENTAGE && j * i > 4)
				{
					m_level->mapData[j][i] = Block::SOFTWALL;
				}
			}
			if (m_level->mapData[j][i] == Block::HARDWALL)
			{
				container->AddEntity(new HardBlock({ x,y }));
			}
			if (m_level->mapData[j][i] == Block::SOFTWALL)
			{
				container->AddEntity(new SoftBlock({ x,y }));
			}
		}
	}
	for (int i = 0; i < m_enemyList->ballom_amount; i++)
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
		container->AddEntity(AddKillableEntity(new Ballom({ setposition.x,setposition.y })));
	}
	return true;
}


uint2 World::GetGridPos(float2 _pixelPosition) const {
	int x = (int)(_pixelPosition.x / BLOCKSIZE);
	int y = (int)((_pixelPosition.y / BLOCKSIZE) - position.y / BLOCKSIZE);
	return { x,y };
}


UINT8 World::GetCurrentBlock(float2 _pixelPosition) const
{
	switch (m_level->mapData[GetGridPos(_pixelPosition).y][GetGridPos(_pixelPosition).x])
	{
	case Block::HARDWALL:
		return Block::HARDWALL;
		break;
	case Block::GRASS:
		return Block::GRASS;
		break;
	case Block::SOFTWALL:
		return Block::SOFTWALL;
		break;
	default:
		return 255;
		break;
	}
}


UINT8 World::GetCurrentBlockFromGrid(uint2 _gridPosition) const
{
	return m_level->mapData[_gridPosition.y][_gridPosition.x];
}


float2 World::GetPixelPosFromGrid(uint2 _gridPosition) const
{
	float x = _gridPosition.x * BLOCKSIZE + position.x;
	float y = _gridPosition.y * BLOCKSIZE + position.y;
	return { x,y };
}

Entity* World::AddKillableEntity(Entity* _entity)
{
	m_killableEntities[m_killableEntitiesAmount++] = _entity;
	return _entity;
}