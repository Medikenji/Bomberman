#pragma once
#include "Entity.h"

class HardBlock : public Entity
{
public:
	HardBlock(float2 _blockPosition);
	~HardBlock() {};

	// Functions
	void Update(float _deltaTime);

private:
	// Variables
	static Surface m_texture;
};

