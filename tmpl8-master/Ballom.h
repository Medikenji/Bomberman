#pragma once
#include "Entity.h"

class World;

class Ballom :    public Entity
{
public:
	Ballom(float2 _ballomPosition);
	~Ballom();

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	void Initialise();
	void SwitchSide();
	void AttemptSwitch();
	void Move(float _deltaTime);

	// Variables
	enum Direction
	{
		X = 0,
		Y = 1
	};

	World* m_currentWorld = nullptr;
	bool m_direction;
	float m_speed;
	float m_directionTimer;
};

