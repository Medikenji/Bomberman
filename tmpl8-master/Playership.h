#pragma once

#include "ActorPool.h"
#include "Bullet.h"

class Bullet;

class Playership : public Actor
{
public:
	Playership();
	bool Tick();
	int GetType() { return Actor::PLAYER; }
private:
	float vx, vy;
	int btimer, dtimer;
	Sprite* death;
};