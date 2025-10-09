#pragma once
#include "Entity.h"

class World;

class BomberMan : public Entity
{
public:
	BomberMan(int _bomberId);
	~BomberMan() {};

	// Functions
	void Update(float _deltaTime);
	static BomberMan** GetPlayers() { return m_players; };
	static int GetPlayerAmount() { return m_playerAmount; };
	static void SetPlayers(BomberMan** _players, int _playerAmount);
	void Die();


private:
	// Functions
	virtual void Initialize();
	bool TileCollision();
	bool SetAnimation(float _velocityX, float _velocityY);
	bool Animate(int _startFrame);
	bool Input(float deltaTime, float* _velocityX, float* _velocityY);

	// Variables
	inline static BomberMan** m_players = nullptr;
	inline static int m_playerAmount;
	World* m_currentWorld = nullptr;
	float m_animationTimer;
	int m_animationState;
	bool m_animationSwitch;
	int m_bomberId;
};

