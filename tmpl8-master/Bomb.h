#pragma once
#include "Entity.h"

class World;

class Bomb : public Entity
{
public:
	Bomb(float2 _bombPosition);
	~Bomb();

	// Functions
	void Update(float _deltaTime);

private:
	// Funtions
	virtual void Initialize();
	bool Animation(float _deltaTime);
	bool Explode();

	// Variables
	World* m_currentWorld = nullptr;
	int m_animationFrame;
	float m_explosionTimer;
	float m_animationTimer;
};

class BombExplosion : public Entity
{
public:
	BombExplosion(float2 _explosionPosition, int _explosionSide, Entity** _killableEntities, int _killableEntitiesAmount);
	~BombExplosion();

	// Enums
	enum {
		MIDDLE = 0,
		LEFT_END = 1,
		LEFT = 2,
		TOP_END = 3,
		TOP = 4,
		RIGHT_END = 5,
		RIGHT = 6,
		BOTTOM_END = 7,
		BOTTOM = 8
	};

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	bool ExplodeAnimation(float _deltaTime);

	// Variables
	static const UINT8 m_spriteAmount = 4;
	Entity* m_killableEntities[32] = { nullptr };
	float4 m_hitbox;
	int m_killableEntitiesAmount;
	int m_explosionType;
	int m_animationFrame;
	float m_animationTimer;
	Sprite* m_sprites[m_spriteAmount];
};