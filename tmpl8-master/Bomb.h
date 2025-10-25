#pragma once
#include "Entity.h"

class World;
class BomberMan;

class Bomb : public Entity
{
public:
	Bomb(float2 _bombPosition, BomberMan* _bomberMan);
	~Bomb();

	// Functions
	void Update(float _deltaTime);

private:
	// Funtions
	virtual void Initialize();
	void Animation(float _deltaTime);
	void Explode();

	// Variables
	World* m_currentWorld = nullptr;
	BomberMan* m_owner;
	uint_fast8_t m_animationFrame;
	float m_explosionTimer;
	float m_animationTimer;
};

class BombExplosion : public Entity
{
public:
	BombExplosion(float2 _explosionPosition, uint_fast8_t _explosionSide, Entity** _killableEntities, int _killableEntitiesAmount);
	~BombExplosion();

	// Enums
	enum ExplosionSide{
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
	int m_killableEntitiesAmount;
	int m_animationFrame;
	float4 m_hitbox;
	uint_fast8_t m_explosionType;
	static const uint_fast8_t m_spriteAmount = 4;
	Entity* m_killableEntities[32] = { nullptr };
	Sprite* m_sprites[m_spriteAmount];
	float m_animationTimer;
};