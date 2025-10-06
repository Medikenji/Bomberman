#include "precomp.h"
#include "Ballom.h"
#include "World.h"

Ballom::Ballom(float2 _ballomPosition)
{
	position = _ballomPosition;
	scale = 16;
	m_speed = 25.0f;
	m_direction = rand() % 2;
	m_directionTimer = (float)((rand() % 9) + 1);
	sprite = new Sprite(new Surface("assets/Ballom.png"), 11);
}


Ballom::~Ballom()
{
	delete sprite;
}


void Ballom::Initialise()
{
	m_currentWorld = static_cast<World*>(container->GetEntityById(0));
}


void Ballom::Update(float _deltaTime)
{
	m_directionTimer -= _deltaTime;
	AttemptSwitch();
	Move(_deltaTime);
	container->DrawToSurfaces(sprite, position);
}


void Ballom::SwitchSide()
{
	uint2 tilePosition = m_currentWorld->GetGridPos(position + scale / 2);
	if (m_direction == Direction::X)
	{
		position.x = m_currentWorld->GetPixelPosFromGrid(tilePosition).x;
	}
	if (m_direction == Direction::Y)
	{
		position.y = m_currentWorld->GetPixelPosFromGrid(tilePosition).y;
	}
	m_directionTimer = (float)((rand() % 9) + 1);
	m_direction = !m_direction;
}


void Ballom::AttemptSwitch()
{
	if (m_directionTimer < 0)
	{
		uint2 tilePosition = m_currentWorld->GetGridPos(position + scale / 2);
		if (m_direction == Direction::X)
		{
			if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePosition[0], (const int)tilePosition[1] - 1 }) == World::GRASS || m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePosition[0], (const int)tilePosition[1] + 1 }) == World::GRASS)
			{
				SwitchSide();
				return;
			}
		}
		if (m_direction == Direction::Y)
		{
			if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePosition[0] - 1, (const int)tilePosition[1] }) == World::GRASS || m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePosition[0] + 1, (const int)tilePosition[1] }) == World::GRASS)
			{
				SwitchSide();
				return;
			}
		}
	}
	return;
}


void Ballom::Move(float _deltaTime)
{
	bool sideA = 0;
	bool sideB = 0;
	uint2 centerTilePos = m_currentWorld->GetGridPos(position + scale / 2);
	uint2 tilePos = m_currentWorld->GetGridPos(position);

	if (m_direction == Direction::X)
	{
		if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)centerTilePos[0] - 1, (const int)centerTilePos[1] }) != World::GRASS)
		{
			sideA = 1;
		}
		if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)centerTilePos[0] + 1, (const int)centerTilePos[1] }) != World::GRASS)
		{
			sideB = 1;
		}
		if (sideA && sideB)
		{
			SwitchSide();
			return;
		}
		if (m_speed < 0 && m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePos.x, (const int)tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		if (m_speed > 0 && m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePos.x + 1, (const int)tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		position.x += m_speed * _deltaTime;
	}
	if (m_direction == Direction::Y)
	{
		if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)centerTilePos[0], (const int)centerTilePos[1] - 1 }) != World::GRASS)
		{
			sideA = 1;
		}
		if (m_currentWorld->GetCurrentBlockFromGrid({ (const int)centerTilePos[0], (const int)centerTilePos[1] + 1 }) != World::GRASS)
		{
			sideB = 1;
		}
		if (sideA && sideB)
		{
			SwitchSide();
			return;
		}
		if (m_speed < 0 && m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePos.x, (const int)tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		if (m_speed > 0 && m_currentWorld->GetCurrentBlockFromGrid({ (const int)tilePos.x, (const int)tilePos.y + 1 }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		position.y += m_speed * _deltaTime;
	}
}