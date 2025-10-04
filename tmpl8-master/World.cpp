#include "precomp.h"
#include "World.h"
#include "HardBlock.h"
#include "SoftBlock.h"
#include "BomberMan.h"
#include "Bomb.h"
#include "Ballom.h"

Level World::m_level;

World::World() {
	srand((unsigned int)time(0));
	m_maxBombAmount = 1;
	m_bombAmount = 0;
	position.y = 32;
	m_grass = new Surface("assets/Grass.png");
}


void World::Initialise()
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		container->AddEntity(new BomberMan());
	}
	GenerateMap();
	for (int i = 0; i < 2000; i++)
	{
		container->AddEntity(new Ballom({ position.x + 16,position.y + 32 }));
	}
}


void World::Update(float _deltaTime)
{
	DrawMap();
}


bool World::PlaceBomb(float2 _position)
{
	if (m_bombAmount < m_maxBombAmount)
	{
		uint2 intGridPos = GetGridPos(_position);
		UINT8 gridPos[2] = { (UINT8)intGridPos.x, (UINT8)intGridPos.y };
		if (m_level.mapData[gridPos[1]][gridPos[0]] != World::Block::GRASS)
			return true;

		m_level.mapData[gridPos[1]][gridPos[0]] = World::Block::BOMB;
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

	container->AddEntity(new BombExplosion(bombPixelPos, BombExplosion::MIDDLE));
	for (int d = 0; d < 4; ++d)
	{
		// Check sides for blocks to break
		for (UINT8 i = 1; i <= explosionSize; ++i)
		{
			int x = bombPos[0] + DIRX[d] * i;
			int y = bombPos[1] + DIRY[d] * i;
			bombPixelPos = GetPixelPosFromGrid({ x,y });
			UINT8& cell = m_level.mapData[y][x];
			if (cell == World::Block::HARDWALL) break;
			if (cell == World::Block::SOFTWALL)
			{
				cell = World::Block::GRASS;
				break;
			}

			// Magic numbers that coincidentally fit with the animation
			const int side = (2 + 2 * d);
			// Spawn in explosion
			if (i == explosionSize)
			{
				container->AddEntity(new BombExplosion(bombPixelPos, side - 1));
				break;
			}
			container->AddEntity(new BombExplosion(bombPixelPos, side));
		}
	}

	m_level.mapData[bombPos[1]][bombPos[0]] = World::Block::GRASS;
	m_bombAmount--;
	return true;
}


bool World::DrawMap()
{
	for (int j = 0; j < m_level.GetMapHeight(); j++)
	{
		for (int i = 0; i < m_level.GetMapWidth(); i++)
		{
			const float x = (float)(i * BLOCKSIZE) + position.x;
			const float y = (float)(j * BLOCKSIZE) + position.y;
			float2 drawPosition = { x,y };
			if (m_level.mapData[j][i] == World::Block::GRASS || m_level.mapData[j][i] == World::Block::BOMB)
			{
				container->CopyToSurfaces(m_grass, drawPosition);
			}
		}
	}
	return true;
}


bool World::GenerateMap()
{
	for (int j = 0; j < m_level.GetMapHeight(); j++)
	{
		for (int i = 0; i < m_level.GetMapWidth(); i++)
		{
			const float x = (float)(i * BLOCKSIZE) + position.x;
			const float y = (float)(j * BLOCKSIZE) + position.y;
			float2 drawPosition = { x,y };
			if (m_level.mapData[j][i] == 2)
			{
				if (rand() % 100 < SOFTBLOCKPERCENTAGE && j * i > 4)
				{
					m_level.mapData[j][i] = World::Block::SOFTWALL;
					//container->AddEntity(new Ballom(drawPosition));

				}
			}
			if (m_level.mapData[j][i] == World::Block::HARDWALL)
			{
				container->AddEntity(new HardBlock({ x,y }));
			}
			if (m_level.mapData[j][i] == World::Block::SOFTWALL)
			{
				container->AddEntity(new SoftBlock({ x,y }));
			}
		}
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
	switch (m_level.mapData[GetGridPos(_pixelPosition).y][GetGridPos(_pixelPosition).x])
	{
	case World::Block::HARDWALL:
		return World::Block::HARDWALL;
		break;
	case World::Block::GRASS:
		return World::Block::GRASS;
		break;
	case World::Block::SOFTWALL:
		return World::Block::SOFTWALL;
		break;
	default:
		return 255;
		break;
	}
}


UINT8 World::GetCurrentBlockFromGrid(uint2 _gridPosition) const
{
	return m_level.mapData[_gridPosition.y][_gridPosition.x];
}


float2 World::GetPixelPosFromGrid(uint2 _gridPosition) const
{
	float x = _gridPosition.x * BLOCKSIZE + position.x;
	float y = _gridPosition.y * BLOCKSIZE + position.y;
	return { x,y };
}