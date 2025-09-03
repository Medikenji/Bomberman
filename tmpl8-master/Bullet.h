#pragma once

#include "ActorPool.h"

class Bullet : public Actor
{
public:
	Bullet();
	~Bullet();
	enum
	{
		PLAYER = 0,
		ENEMY = 1
	};
	void Init(Surface* a_Surface, float a_X, float a_Y, float a_VX, float a_VY, int a_Owner)
	{
		x = a_X, y = a_Y;
		vx = a_VX, vy = a_VY;
		surface = a_Surface;
		life = 1200;
		owner = a_Owner;
	}
	bool Tick();
	int GetType() { return Actor::BULLET; }
	float vx, vy;
	int life, owner;
	Sprite* player, * enemy;
};