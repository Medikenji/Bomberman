#include "precomp.h"
#include "SoftBlock.h"
#include "World.h"

SoftBlock::SoftBlock(float2 setposition)
{
	position = setposition;
	// artificial width and height
	scale = { 16, 16 };
	sprite = new Sprite(new Surface("assets/SoftBlock.png"), 7);;
	m_currentFrame = 0;
	sprite->SetFrame(m_currentFrame);
	m_animationTimer = 0.1f;
}

void SoftBlock::Initialise()
{
	m_currentWorld = static_cast<World*>(GetEntityById(0));
}

void SoftBlock::Update(float deltaTime)
{
	DrawToSurfaces(sprite, position.x, position.y);
	if (m_currentWorld->GetCurrentBlock(position) != Entity::SOFTWALL)
		BeDestroyed(deltaTime);
}

bool SoftBlock::BeDestroyed(float deltaTime)
{
	m_animationTimer -= deltaTime;
	if (m_animationTimer < 0)
	{
		if (++m_currentFrame == 7)
		{
			Entity::DeleteEntity(this);
			return true;
		}
		m_animationTimer = 0.1f;
		sprite->SetFrame(m_currentFrame);
	}
	return true;
}