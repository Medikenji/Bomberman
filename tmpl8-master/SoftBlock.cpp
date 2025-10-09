#include "precomp.h"
#include "SoftBlock.h"
#include "World.h"

SoftBlock::SoftBlock(float2 _blockPosition)
{
	position = _blockPosition;
	// artificial width and height
	scale = { 16, 16 };
	sprite = new Sprite(new Surface("assets/SoftBlock.png"), 7);;
	m_currentFrame = 0;
	sprite->SetFrame(m_currentFrame);
	m_animationTimer = 0.1f;
}


SoftBlock::~SoftBlock()
{
	delete sprite;
}


void SoftBlock::Initialize()
{
	m_currentWorld = static_cast<World*>(container->GetEntityById(0));
}


void SoftBlock::Update(float _deltaTime)
{
	container->DrawToSurfaces(sprite, position);
	if (m_currentWorld->GetCurrentBlock(position) != World::Block::SOFTWALL)
		BeDestroyed(_deltaTime);
}


bool SoftBlock::BeDestroyed(float _deltaTime)
{
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		if (++m_currentFrame == 7)
		{
			container->DeleteEntity(this);
			return true;
		}
		m_animationTimer = 0.1f;
		sprite->SetFrame(m_currentFrame);
	}
	return true;
}