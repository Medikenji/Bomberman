#pragma once

#include "ActorPool.h"
#include "Bullet.h"
#include "Playership.h"

class Bullet;

class Enemy : public Actor
{
public:
	Enemy();
	bool Tick();
	int GetType() { return Actor::ENEMY; }
private:
	float vx, vy;
	int frame, btimer, dtimer;
	Sprite* death;
};

