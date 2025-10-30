#include "precomp.h"
#include "Bomb.h"
#include "World.h"
#include "AudioManager.h"
#include "Collision.h"
#include "BomberMan.h"

Bomb::Bomb(float2 _bombPosition, BomberMan* _bomberMan)
{
	position = _bombPosition;
	m_owner = _bomberMan;
	m_owner->BombAmount(1);
	m_animationFrame = 0;
	m_explosionTimer = 3.0f;
	m_animationTimer = 0.0f;
	AddSprite(new Sprite(new Surface("assets/Bomb.png"), 3));
	m_sprite->SetFrame(m_animationFrame);
}


Bomb::~Bomb()
{
	delete m_sprite;
}


void Bomb::Initialize()
{
	m_currentWorld = static_cast<World*>(m_container->GetEntityById(0));
}


void Bomb::Update(float _deltaTime)
{
	m_container->DrawToSurfaces(m_sprite, position, this);
	Animation(_deltaTime);
}


void Bomb::Animation(float _deltaTime)
{
	m_explosionTimer -= _deltaTime;
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		if (++m_animationFrame == 3)
		{
			m_animationFrame = 0;
		}
		m_currentFrame = m_animationFrame;
		m_animationTimer = 0.05f;
	}
	if (m_explosionTimer < 0)
	{
		m_owner->BombAmount(0);
		Explode();
	}
}


void Bomb::Explode()
{
	AudioManager::GetAudioManager()->PlayAudio(Audio::BombExplode);
	m_currentWorld->ExplodeBomb(m_currentWorld->GetGridPos(position), m_owner->GetBombRadius());
	m_container->DeleteEntity(this);
}


BombExplosion::BombExplosion(float2 _explosionPosition, uint_fast8_t _explosionSide, Entity** _killableEntities, int _killableEntitiesAmount)
{
	position = _explosionPosition;
	scale = { 16.0f,16.0f };
	m_explosionType = _explosionSide;
	m_currentFrame = m_explosionType;
	m_killableEntitiesAmount = _killableEntitiesAmount;
	m_hitbox = { GetRectangle().x+3 , GetRectangle().y+3 , GetRectangle().w-6 , GetRectangle().z-6 };
	m_animationTimer = 0.15f;
	m_animationFrame = 0;
	m_sprites[0] = new Sprite(new Surface("assets/ExplosionI.png"), 9);
	m_sprites[1] = new Sprite(new Surface("assets/ExplosionII.png"), 9);
	m_sprites[2] = new Sprite(new Surface("assets/ExplosionIII.png"), 9);
	m_sprites[3] = new Sprite(new Surface("assets/ExplosionIV.png"), 9);
	AddSprite(m_sprites[m_animationFrame]);
	m_sprite->SetFrame(m_explosionType);
	for (int i = 0; i < m_killableEntitiesAmount; i++)
	{
		m_killableEntities[i] = _killableEntities[i];
	}
}


BombExplosion::~BombExplosion()
{
	for (uint_fast8_t i = 0; i < m_spriteAmount; ++i)
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
		m_container->DrawToSurfaces(m_sprite, position, this);
}


bool BombExplosion::ExplodeAnimation(float _deltaTime)
{
	m_animationTimer -= _deltaTime;
	if (m_animationTimer < 0)
	{
		m_animationTimer = 0.15f;
		m_sprite = m_sprites[m_animationFrame];
		m_currentFrame = m_explosionType;
		if (++m_animationFrame == 5)
		{
			m_container->DeleteEntity(this);
			return 0;
		}
	}
	return 1;
}