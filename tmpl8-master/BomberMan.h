#pragma once
#include "Entity.h"
class World;

class BomberMan : public Entity
{
public:
	BomberMan();
	~BomberMan();

	// Functions
	void Update(float deltaTime);

private:
	// Functions
	virtual void Initialise();
	bool TileCollision();
	bool SetAnimation(float vx, float vy);
	bool Animate(int startFrame);
	bool Input(float deltaTime, float* vx, float* vy);;

	// Variables
	static int m_nextBomberId;
	World* m_currentWorld;
	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	int m_bomberId;
};

