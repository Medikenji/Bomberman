#pragma once
#include "Entity.h"

class World;

class BomberMan : public Entity
{
public:
	BomberMan(int _bomberId);
	~BomberMan();

	// Functions
	void Update(float _deltaTime);
	static BomberMan** GetPlayers() { return m_players; };
	static void DeletePlayers();
	static int GetPlayerAmount() { return m_playerAmount; };
	static void SetCurrentWorld(World* _currentWorld);
	static void SetPlayers(BomberMan** _players, int _playerAmount);
	void BombAmount(bool _add_or_subtract);
	uint_fast8_t GetBombRadius()const { return m_bombRadius; };
	bool AddBombRadius();
	bool AddSpeed();
	void GoDie();


private:
	// Functions
	void TileCollision();
	void SetAnimation(float _velocityX, float _velocityY);
	void Animate(uint_fast8_t _startFrame);
	void Input(float deltaTime, float* _velocityX, float* _velocityY);

	// Variables
	const static uint_fast8_t MAX_BOMB_RADIUS = 10;
	const static uint_fast8_t START_SPEED = 45;
	inline static BomberMan** m_players = nullptr;
	inline static int m_playerAmount;
	uint_fast8_t m_placedBombs;
	uint_fast8_t m_maxPlacedBombs;
	uint_fast8_t m_bombRadius;
	World* m_currentWorld = nullptr;
	uint_fast8_t m_animationState;
	float m_animationTimer;
	bool m_animationSwitch;
	int m_bomberId;
	float m_speed;
};

