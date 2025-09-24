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


bool Bomb::ExplodeAnimation(float deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer < 0)
	{
		Explode();
	}
	return true;
}


bool Bomb::Explode()
{
	m_currentWorld->ExplodeBomb({ m_currentWorld->GetGridPos(position)[1],m_currentWorld->GetGridPos(position)[0] });
	Entity::DeleteEntity(this);
	return true;
}


BombExplosion::BombExplosion(float2 setposition, int type)
{
	position = setposition;
	m_explosionType = type;
	m_animationTimer = 0.15f;
	m_animationFrame = 0;
	m_sprites[0] = new Sprite(new Surface("assets/ExplosionI.png"), 9);
	m_sprites[1] = new Sprite(new Surface("assets/ExplosionII.png"), 9);
	m_sprites[2] = new Sprite(new Surface("assets/ExplosionIII.png"), 9);
	m_sprites[3] = new Sprite(new Surface("assets/ExplosionIV.png"), 9);
	sprite = m_sprites[m_animationFrame];
	sprite->SetFrame(m_explosionType);
}


void BombExplosion::Update(float deltaTime)
{
	if(ExplodeAnimation(deltaTime))
	DrawToSurfaces(sprite, position.x, position.y);
}


bool BombExplosion::ExplodeAnimation(float deltaTime)
{
	m_animationTimer -= deltaTime;
	if (m_animationTimer < 0)
	{
		m_animationTimer = 0.15f;
		sprite = m_sprites[m_animationFrame];
		sprite->SetFrame(m_explosionType);
		if (++m_animationFrame == 4)
		{
			Entity::DeleteEntity(this);
			return false;
		}
	}
	return true;
}