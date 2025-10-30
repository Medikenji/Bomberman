#pragma once
#include "Enemy.h"

class World;

class Dahl : public Enemy
{
public:
	Dahl();
	~Dahl();

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	void Initialize();
	void SwitchSide();
	void AttemptSwitch();
	void Move(float _deltaTime);

	// Enums
	enum Direction
	{
		X = 0,
		Y = 1
	};

	// Variables
	bool m_direction;
	float m_speed;
	float m_directionTimer;
};

