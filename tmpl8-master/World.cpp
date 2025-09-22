#include "precomp.h"
#include "World.h"
#include "HardBlock.h"
#include "SoftBlock.h"
#include "BomberMan.h"
#include "Bomb.h"

Level* World::currentLevel;

World::World() {
	srand(time(0));
	m_maxBombAmount = 3;
	m_bombAmount = 0;
	m_blocksGenerated = false;
	position.y = 32;
	m_grass = new Surface("assets/Grass.png");
	InitialiseLevels();
	currentLevel = level1;
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

int World::GetCurrentBlock(float2 position)
{
	switch (currentLevel->mapData[GetGridPos(position)[1]][GetGridPos(position)[0]])
	{
	case 1:
		return Entity::HARDWALL;
		break;
	case 2:
		return Entity::GRASS;
		break;
	case 3:
		return Entity::SOFTWALL;
		break;
	default:
		return -1;
		break;
		return 0;
	}
}

UINT8 World::GetCurrentBlockFromGrid(int2 gridposition)
{
	switch (currentLevel->mapData[gridposition.y][gridposition.x])
	{
	case 1:
		return Entity::HARDWALL;
		break;
	case 2:
		return Entity::GRASS;
		break;
	case 3:
		return Entity::BOMB;
		break;
	default:
		return -1;
		break;
		return 0;
	}
}

float2 World::GetPixelPosFromGrid(int2 gridPosition)
{
	float x = gridPosition.x * BLOCKSIZE + position.x;
	float y = gridPosition.y * BLOCKSIZE + position.y;
	return { x,y };
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
				if (rand() % 100 < SOFTBLOCKPERCENTAGE && !m_blocksGenerated && j*i > 4)
				{
					currentLevel->mapData[j][i] = 4;
				}
			}
			if (currentLevel->mapData[j][i] == 2)
			{
				CopyToSurfaces(m_grass, x, y);
			}
			if (currentLevel->mapData[j][i] == 1 && !m_blocksGenerated)
			{
				AddEntity(new HardBlock({ x,y }));
			}
			if (currentLevel->mapData[j][i] == 4 && !m_blocksGenerated)
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
	level1 = new Level(25, 13);
	level1->mapData = new UINT8[13][50]
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

void World::ExplodeBomb(UINT8* gridposition)
{
	currentLevel->mapData[gridposition[1]][gridposition[0]] = 2;
	m_bombAmount--;
}

UINT8* World::GetGridPos(float2& pixelPos) {
	int x = (int)(pixelPos.x / BLOCKSIZE);
	int y = (int)(pixelPos.y / BLOCKSIZE) - position.y / BLOCKSIZE;
	UINT8 gridPos[2] = { x,y };
	return gridPos;
}

void World::PlaceBomb(float2 position)
{
	if (m_bombAmount < m_maxBombAmount)
	{
		UINT8* gridPos = GetGridPos(position);
		if (currentLevel->mapData[gridPos[1]][gridPos[0]] == 3)
			return;

		currentLevel->mapData[gridPos[1]][gridPos[0]] = 3;
		AddEntity(new Bomb(GetPixelPosFromGrid({ gridPos[0], gridPos[1] })));
		m_bombAmount++;
	}
}