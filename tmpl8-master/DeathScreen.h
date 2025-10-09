#pragma once
#include "Entity.h"
class DeathScreen : public Entity
{
public:
	DeathScreen();
	~DeathScreen();

	// Functions
	void Update(float _deltaTime);

private:
	Surface* m_backGround = nullptr;
};

