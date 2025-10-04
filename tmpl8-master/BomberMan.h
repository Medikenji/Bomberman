#pragma once
#include "Entity.h"
class World;

class BomberMan : public Entity
{
public:
	BomberMan();
	~BomberMan() {};

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	virtual void Initialise();
	bool TileCollision();
	bool SetAnimation(float _velocityX, float _velocityY);
	bool Animate(int _startFrame);
	bool Input(float deltaTime, float* _velocityX, float* _velocityY);

	// Variables
	static int m_nextBomberId;
	World* m_currentWorld = nullptr;
	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	int m_bomberId;
};

