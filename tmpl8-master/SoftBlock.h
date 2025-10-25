#pragma once
#include "Entity.h"

class World;

// Enums
enum BlockContent {
	EMPTY = 0,
	EXIT = 1,
	PW_SKATE = 2,
	PW_FIRE = 3,
};

class SoftBlock : public Entity
{
public:
	SoftBlock(float2 _blockPosition, BlockContent _content = EMPTY);
	~SoftBlock();

	// Functions
	void Update(float _deltaTime);

private:
	// Functions
	virtual void Initialize();
	void BeDestroyed(float _deltaTime);

	// Variables
	World* m_currentWorld = nullptr;
	float m_animationTimer;
	BlockContent m_content;
};

