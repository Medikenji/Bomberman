#pragma once
#include "Entity.h"

class BomberMan : public Entity
{
public:
	BomberMan();
	~BomberMan();
	void Update(float deltaTime);

private:
	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	bool SetAnimation(float vx, float vy);
	bool Animate(int startFrame);
};

