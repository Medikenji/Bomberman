#include "precomp.h"
#include "Bomb.h"
#include "World.h"

Bomb::Bomb(float2 _bombPosition)
{
	position = _bombPosition;
	sprite = new Sprite(new Surface("assets/Bomb.png"), 3);
	m_timer = 3.0f;
}


Bomb::~Bomb()
{
	delete sprite;
}


void Bomb::Initialise()
{
	m_currentWorld = static_cast<World*>(container->GetEntityById(0));
}


void Bomb::Update(float _deltaTime)
{
	container->DrawToSurfaces(sprite, position);
	ExplodeAnimation(_deltaTime);
}


bool Bomb::ExplodeAnimation(float _deltaTime)
{
	m_timer -= _deltaTime;
	if (m_timer < 0)
	{
		Explode();
	}
	return true;
}


bool Bomb::Explode()
{
	m_currentWorld->ExplodeBomb(m_currentWorld->GetGridPos(position));
	container->DeleteEntity(this);
	return true;
}


BombExplosion::BombExplosion(float2 _explosionPosition, int _explosionSide)
{
	position = _explosionPosition;
	m_explosionType = _explosionSide;
	m_animationTimer = 0.15f;
	m_animationFrame = 0;
	m_sprites[0] = new Sprite(new Surface("assets/ExplosionI.png"), 9);
	m_sprites[1] = new Sprite(new Surface("assets/ExplosionII.png"), 9);
	m_sprites[2] = new Sprite(new Surface("assets/ExplosionIII.png"), 9);
	m_sprites[3] = new Sprite(new Surface("assets/ExplosionIV.png"), 9);
	sprite = m_sprites[m_animationFrame];
	sprite->SetFrame(m_explosionType);
}


BombExplosion::~BombExplosion()
{
	for (UINT8 i = 0; i < m_spriteAmount; ++i)
	{
		delete m_sprites[i];
	}
}


void BombExplosion::Update(float _deltaTime)
{
	if (ExplodeAnimation(_deltaTime))
		container->DrawToSurfaces(sprite, position);
}


bool BombExplosion::ExplodeAnimation(float _deltaTime)
{
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		m_animationTimer = 0.15f;
		sprite = m_sprites[m_animationFrame];
		sprite->SetFrame(m_explosionType);
		if (++m_animationFrame == 4)
		{
			container->DeleteEntity(this);
			return false;
		}
	}
	return true;
}