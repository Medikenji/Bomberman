#include "precomp.h"
#include "World.h"
#include "HardBlock.h"
#include "SoftBlock.h"
#include "BomberMan.h"
#include "Bomb.h"

Level* World::currentLevel;

World::World() {
	srand(time(0));
	m_maxBombAmount = 1;
	m_bombAmount = 0;
	m_blocksGenerated = false;
	position.y = 32;
	m_grass = new Surface("assets/Grass.png");
	InitialiseLevels();
	currentLevel = m_level1;
}


void World::Initialise()
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
		AddEntity(new BomberMan());
}


void World::Update(float deltaTime)
{
	DrawMap();
}


bool World::PlaceBomb(float2 position)
{
	if (m_bombAmount < m_maxBombAmount)
	{
		UINT8* gridPos = GetGridPos(position);
		if (currentLevel->mapData[gridPos[1]][gridPos[0]] != Entity::GRASS)
			return true;

		currentLevel->mapData[gridPos[1]][gridPos[0]] = Entity::BOMB;
		AddEntity(new Bomb(GetPixelPosFromGrid({ gridPos[0], gridPos[1] })));
		m_bombAmount++;
	}
	return true;
}


bool World::ExplodeBomb(int2 gridposition)
{
	const int DIRX[4] = { -1, 0, 1, 0 };
	const int DIRY[4] = { 0, -1, 0, 1 };

	UINT8 explosionSize = 5;
	UINT8 bombPos[2] = { gridposition.y,gridposition.x };
	float2 bombPixelPos = GetPixelPosFromGrid({ gridposition.y,gridposition.x });

	Entity::AddEntity(new BombExplosion(bombPixelPos, BombExplosion::MIDDLE));
	for (int d = 0; d < 4; ++d)
	{
		// Check sides for blocks to break
		for (UINT8 i = 1; i <= explosionSize; ++i)
		{
			int x = bombPos[0] + DIRX[d] * i;
			int y = bombPos[1] + DIRY[d] * i;
			bombPixelPos = GetPixelPosFromGrid({ x,y });
			UINT8& cell = currentLevel->mapData[y][x];
			if (cell == Entity::HARDWALL) break;
			if (cell == Entity::SOFTWALL)
			{
				cell = Entity::GRASS;
				break;
			}

			// Magic numbers that coincidentally fit with the animation
			const int side = (2 + 2 * d);
			// Spawn in explosion
			if (i == explosionSize)
			{
				Entity::AddEntity(new BombExplosion(bombPixelPos, side - 1));
				break;
			}
			Entity::AddEntity(new BombExplosion(bombPixelPos, side));
		}
	}

	currentLevel->mapData[bombPos[1]][bombPos[0]] = Entity::GRASS;
	m_bombAmount--;
	return true;
}


bool World::DrawMap()
{
	for (int j = 0; j < currentLevel->getMapHeight(); j++)
	{
		for (int i = 0; i < currentLevel->getMapWidth(); i++)
		{
			float x = (i * BLOCKSIZE) + position.x;
			float y = (j * BLOCKSIZE) + position.y;
			if (currentLevel->mapData[j][i] == 2)
			{
				if (rand() % 100 < SOFTBLOCKPERCENTAGE && !m_blocksGenerated && j * i > 4)
				{
					currentLevel->mapData[j][i] = Entity::SOFTWALL;
				}
			}
			if (currentLevel->mapData[j][i] == Entity::GRASS || currentLevel->mapData[j][i] == Entity::BOMB)
			{
				CopyToSurfaces(m_grass, x, y);
			}
			if (currentLevel->mapData[j][i] == Entity::HARDWALL && !m_blocksGenerated)
			{
				AddEntity(new HardBlock({ x,y }));
			}
			if (currentLevel->mapData[j][i] == Entity::SOFTWALL && !m_blocksGenerated)
			{
				AddEntity(new SoftBlock({ x,y }));
			}
		}
	}
	m_blocksGenerated = true;
	return true;
}


bool World::InitialiseLevels()
{
	m_level1 = new Level(25, 13);
	m_level1->mapData = new UINT8[13][26]
	{
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
	return true;
}


UINT8* World::GetGridPos(float2& pixelPos) const {
	int x = (int)(pixelPos.x / BLOCKSIZE);
	int y = (int)(pixelPos.y / BLOCKSIZE) - position.y / BLOCKSIZE;
	UINT8 gridPos[2] = { x,y };
	return gridPos;
}


int World::GetCurrentBlock(float2 position) const
{
	switch (currentLevel->mapData[GetGridPos(position)[1]][GetGridPos(position)[0]])
	{
	case Entity::HARDWALL:
		return Entity::HARDWALL;
		break;
	case Entity::GRASS:
		return Entity::GRASS;
		break;
	case Entity::SOFTWALL:
		return Entity::SOFTWALL;
		break;
	default:
		return -1;
		break;
		return 0;
	}
}


UINT8 World::GetCurrentBlockFromGrid(int2 gridposition) const
{
	switch (currentLevel->mapData[gridposition.y][gridposition.x])
	{
	case Entity::HARDWALL:
		return Entity::HARDWALL;
		break;
	case Entity::GRASS:
		return Entity::GRASS;
		break;
	case Entity::SOFTWALL:
		return Entity::SOFTWALL;
		break;
	default:
		return -1;
		break;
		return 0;
	}
}


float2 World::GetPixelPosFromGrid(int2 gridPosition) const
{
	float x = gridPosition.x * BLOCKSIZE + position.x;
	float y = gridPosition.y * BLOCKSIZE + position.y;
	return { x,y };
}