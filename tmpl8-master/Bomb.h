#pragma once
#include "Entity.h"

class World;

class Bomb : public Entity
{
public:
	Bomb(float2 Position);
	void Update(float deltaTime);

private:
	virtual void Initialise();
	void ExplodeAnimation(float deltaTime);
	void Explode();
	World* m_currentWorld;
	float m_timer;
};

