#include "precomp.h"
#include "SoftBlock.h"
#include "World.h"
#include "Interactable.h"

SoftBlock::SoftBlock(float2 _blockPosition, BlockContent _content)
{
	position = _blockPosition;
	scale = 15;
	AddSprite(new Sprite(new Surface("assets/SoftBlock.png"), 7));
	m_currentFrame = 0;
	m_sprite->SetFrame(m_currentFrame);
	m_animationTimer = 0.1f;
	m_content = _content;
}


SoftBlock::~SoftBlock()
{
	delete m_sprite;
}


void SoftBlock::Initialize()
{
	m_currentWorld = static_cast<World*>(m_container->GetEntityById(0));
}


void SoftBlock::Update(float _deltaTime)
{
	m_container->DrawToSurfaces(m_sprite, position, this);
	if (m_content != BlockContent::EMPTY)
		m_container->BoxToSurfaces(0x00ff00, GetRectangle());

	if (m_currentWorld->GetCurrentBlock(position) != World::Block::SOFTWALL)
		BeDestroyed(_deltaTime);

}


void SoftBlock::BeDestroyed(float _deltaTime)
{
	if (m_content != BlockContent::EMPTY)
	{
		m_container->AddEntity(new Interactable(position, m_content));
		m_container->DeleteEntity(this);
		return;
	}
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		if (++m_currentFrame == 7)
		{
			m_container->DeleteEntity(this);
			return;
		}
		m_animationTimer = 0.1f;
	}
}