#include "precomp.h"
#include "Dahl.h"
#include "World.h"

Dahl::Dahl()
{
	m_speed = 35.0f;
	m_direction = Direction::X;
	m_directionTimer = (((float)rand() / (float)RAND_MAX) * 10 + 1);
	AddSprite(new Sprite(new Surface("assets/Dahl.png"), 11));
}


Dahl::~Dahl()
{
	delete m_sprite;
}


void Dahl::Initialize()
{
	m_currentWorld = static_cast<World*>(m_container->GetEntityById(0));
}


void Dahl::Update(float _deltaTime)
{
	m_directionTimer -= _deltaTime;
	AttemptSwitch();
	Move(_deltaTime);
	PlayerCollision();
	m_container->DrawToSurfaces(m_sprite, position, this);
	if (m_isDead)
		GoDie();
}


void Dahl::SwitchSide()
{
	uint2 tilePosition = m_currentWorld->GetGridPos(position + scale / 2);
	float2 newPosisition = m_currentWorld->GetPixelPosFromGrid(tilePosition);
	if (m_direction == Direction::X)
	{
		position.x = newPosisition.x;
		m_directionTimer = (((float)rand() / (float)RAND_MAX) * 2 + 1);
	}
	if (m_direction == Direction::Y)
	{
		position.y = newPosisition.y;
		m_directionTimer = (((float)rand() / (float)RAND_MAX) * 10 + 1);
	}
	m_direction = !m_direction;
}


void Dahl::AttemptSwitch()
{
	if (m_directionTimer < 0)
	{
		uint2 tilePosition = m_currentWorld->GetGridPos(position + scale / 2);
		float2 newPosisition = m_currentWorld->GetPixelPosFromGrid(tilePosition);
		if (m_direction == Direction::X)
		{
			if ((m_currentWorld->GetCurrentBlockFromGrid({ tilePosition[0], tilePosition[1] - 1 }) == World::GRASS || m_currentWorld->GetCurrentBlockFromGrid({ tilePosition[0], tilePosition[1] + 1 }) == World::GRASS) && abs(position.x - newPosisition.x) < 0.1f)
			{
				SwitchSide();
				return;
			}
		}
		if (m_direction == Direction::Y)
		{
			if ((m_currentWorld->GetCurrentBlockFromGrid({ tilePosition[0] - 1,tilePosition[1] }) == World::GRASS || m_currentWorld->GetCurrentBlockFromGrid({ tilePosition[0] + 1, tilePosition[1] }) == World::GRASS) && abs(position.y - newPosisition.y) < 0.1f)
			{
				SwitchSide();
				return;
			}
		}
	}
	return;
}


void Dahl::Move(float _deltaTime)
{
	bool sideA = 0;
	bool sideB = 0;
	uint2 centerTilePos = m_currentWorld->GetGridPos(position + scale / 2);
	uint2 tilePos = m_currentWorld->GetGridPos(position);

	if (m_direction == Direction::X)
	{
		if (m_currentWorld->GetCurrentBlockFromGrid({ centerTilePos[0] - 1, centerTilePos[1] }) != World::GRASS)
		{
			sideA = 1;
		}
		if (m_currentWorld->GetCurrentBlockFromGrid({ centerTilePos[0] + 1, centerTilePos[1] }) != World::GRASS)
		{
			sideB = 1;
		}
		if (sideA && sideB)
		{
			SwitchSide();
			return;
		}
		if (m_speed < 0 && m_currentWorld->GetCurrentBlockFromGrid({ tilePos.x, tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		if (m_speed > 0 && m_currentWorld->GetCurrentBlockFromGrid({ tilePos.x + 1, tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		position.x += m_speed * _deltaTime;
	}
	if (m_direction == Direction::Y)
	{
		if (m_currentWorld->GetCurrentBlockFromGrid({ centerTilePos[0], centerTilePos[1] - 1 }) != World::GRASS)
		{
			sideA = 1;
		}
		if (m_currentWorld->GetCurrentBlockFromGrid({ centerTilePos[0], centerTilePos[1] + 1 }) != World::GRASS)
		{
			sideB = 1;
		}
		if (sideA && sideB)
		{
			SwitchSide();
			return;
		}
		if (m_speed < 0 && m_currentWorld->GetCurrentBlockFromGrid({ tilePos.x, tilePos.y }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		if (m_speed > 0 && m_currentWorld->GetCurrentBlockFromGrid({ tilePos.x, tilePos.y + 1 }) != World::GRASS)
		{
			m_speed = -m_speed;
		}
		position.y += m_speed * _deltaTime;
	}
}