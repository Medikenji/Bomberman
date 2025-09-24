#pragma once
#include "Entity.h"

class World;

class SoftBlock : public Entity
{
public:
	SoftBlock(float2 setposition);

	// Functions
	void Update(float deltaTime);

private:
	// Functions
	virtual void Initialise();
	bool BeDestroyed(float deltaTime);

	// Variables
	World* m_currentWorld;
	float m_animationTimer;
	int m_currentFrame;
};

