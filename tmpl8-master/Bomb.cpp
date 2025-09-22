#include "precomp.h"
#include "Bomb.h"
#include "World.h"

Bomb::Bomb(float2 setposition)
{
	position = setposition;
	sprite = new Sprite(new Surface("assets/Bomb.png"), 3);
	m_timer = 3.0f;
}

void Bomb::Initialise()
{
	m_currentWorld = static_cast<World*>(GetEntityById(0));
}

void Bomb::Update(float deltaTime)
{
	DrawToSurfaces(sprite, position.x, position.y);
	ExplodeAnimation(deltaTime);
}

void Bomb::ExplodeAnimation(float deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer < 0)
	{
		Explode();
	}
}

void Bomb::Explode()
{
	m_currentWorld->ExplodeBomb(m_currentWorld->GetGridPos(position));
	DeleteEntity(this);
}