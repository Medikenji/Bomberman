#pragma once

#include "ActorPool.h"

class BomberMan : public Actor
{
	BomberMan();
	~BomberMan();
	bool Tick();
	int GetType() { return Actor::PLAYER; }
};

