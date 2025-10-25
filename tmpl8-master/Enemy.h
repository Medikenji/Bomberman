#pragma once
#include "Entity.h"

class BomberMan;

class Enemy : public Entity
{
public:
	Enemy();
	virtual ~Enemy() {};

protected:
	void PlayerCollision();
	void GoDie();

private:
};

