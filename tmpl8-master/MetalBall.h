#pragma once

#include "ActorPool.h"

class MetalBall : public Actor
{
public:
	MetalBall();
	bool Tick();
	bool Hit(float& a_X, float& a_Y, float& a_NX, float& a_NY);
	int GetType() { return Actor::METALBALL; }
};

