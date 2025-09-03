#pragma once

#include "ActorPool.h"

class BomberMan : public Actor
{
public:
	BomberMan();
	~BomberMan();
	bool Tick(float deltaTime);
	int GetType() { return Actor::PLAYER; }

private:
	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	bool SetAnimation(float vx, float vy);
	bool Animate(int startFrame);
};

