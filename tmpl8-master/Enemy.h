#pragma once
#include "Entity.h"

class World;

class Enemy : public Entity
{
public:
	Enemy();
	virtual ~Enemy() {};

protected:
	void PlayerCollision();
	void GoDie();
	World* m_currentWorld = nullptr;
	uint_fast16_t m_score;
};

