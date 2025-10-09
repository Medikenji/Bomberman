#include "precomp.h"
#include "Bomb.h"
#include "World.h"
#include "AudioManager.h"
#include "Collision.h"

Bomb::Bomb(float2 _bombPosition)
{
	position = _bombPosition;
	m_animationFrame = 0;
	m_explosionTimer = 3.0f;
	m_animationTimer = 0.0f;
	sprite = new Sprite(new Surface("assets/Bomb.png"), 3);
	sprite->SetFrame(m_animationFrame);
}


Bomb::~Bomb()
{
	delete sprite;
}


void Bomb::Initialize()
{
	m_currentWorld = static_cast<World*>(container->GetEntityById(0));
}


void Bomb::Update(float _deltaTime)
{
	container->DrawToSurfaces(sprite, position);
	Animation(_deltaTime);
}


bool Bomb::Animation(float _deltaTime)
{
	m_explosionTimer -= _deltaTime;
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		if (++m_animationFrame == 3)
		{
			m_animationFrame = 0;
		}
		sprite->SetFrame(m_animationFrame);
		m_animationTimer = 0.05f;
	}
	if (m_explosionTimer < 0)
	{
		Explode();
	}
	return true;
}


bool Bomb::Explode()
{
	AudioManager::PlayAudio(Audio::BombExplode);
	m_currentWorld->ExplodeBomb(m_currentWorld->GetGridPos(position));
	container->DeleteEntity(this);
	return true;
}


BombExplosion::BombExplosion(float2 _explosionPosition, int _explosionSide, Entity** _killableEntities, int _killableEntitiesAmount)
{
	position = _explosionPosition;
	scale = { 16.0f,16.0f };
	m_explosionType = _explosionSide;
	m_killableEntitiesAmount = _killableEntitiesAmount;
	m_hitbox = { GetRectangle().x+3 , GetRectangle().y+3 , GetRectangle().w-6 , GetRectangle().z-6 };
	m_animationTimer = 0.15f;
	m_animationFrame = 0;
	m_sprites[0] = new Sprite(new Surface("assets/ExplosionI.png"), 9);
	m_sprites[1] = new Sprite(new Surface("assets/ExplosionII.png"), 9);
	m_sprites[2] = new Sprite(new Surface("assets/ExplosionIII.png"), 9);
	m_sprites[3] = new Sprite(new Surface("assets/ExplosionIV.png"), 9);
	sprite = m_sprites[m_animationFrame];
	sprite->SetFrame(m_explosionType);
	for (int i = 0; i < m_killableEntitiesAmount; i++)
	{
		m_killableEntities[i] = _killableEntities[i];
	}
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

	for (int i = 0; i < m_killableEntitiesAmount; i++)
	{
		if (Collision::RecToRec(m_hitbox, m_killableEntities[i]->GetRectangle()))
			m_killableEntities[i]->Die();
	}
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