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
	virtual void Initialise();
	bool ExplodeAnimation(float _deltaTime);
	bool Explode();

	// Variables
	World* m_currentWorld = nullptr;
	float m_timer;
};

class BombExplosion : public Entity
{
public:
	BombExplosion(float2 _explosionPosition, int _explosionSide);
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
	int m_explosionType;
	int m_animationFrame;
	float m_animationTimer;
	Sprite* m_sprites[m_spriteAmount];
};