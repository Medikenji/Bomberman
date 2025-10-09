#pragma once
#include "Enemy.h"

class World;

class Ballom : public Enemy
{
public:
	Ballom(float2 _ballomPosition);
	~Ballom();

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
	World* m_currentWorld = nullptr;
	bool m_direction;
	float m_speed;
	float m_directionTimer;
};

