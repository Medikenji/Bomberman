#pragma once

#include "ActorPool.h"
#include "Bullet.h"

class Bullet;

#define STARS		500

class Starfield : public Actor
{
public:
	Starfield();
	bool Tick();
private:
	float* x, * y;
};
