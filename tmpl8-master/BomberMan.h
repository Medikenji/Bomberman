#pragma once
#include "Entity.h"
class World;

class BomberMan : public Entity
{
public:
	BomberMan();
	~BomberMan();
	void Update(float deltaTime);

private:
	virtual void Initialise();
	void TileCollision();
	bool SetAnimation(float vx, float vy);
	bool Animate(int startFrame);
	void Input(float deltaTime, float* vx, float* vy);;

	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	static int m_nextBomberId;
	int m_bomberId;
	World* m_currentWorld;
};

