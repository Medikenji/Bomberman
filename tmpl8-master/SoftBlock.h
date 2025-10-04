#pragma once
#include "Entity.h"

class World;

class SoftBlock : public Entity
{
public:
	SoftBlock(float2 _blockPosition);
	~SoftBlock();

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	virtual void Initialise();
	bool BeDestroyed(float _deltaTime);

	// Variables
	World* m_currentWorld = nullptr;
	float m_animationTimer;
	int m_currentFrame;
};

