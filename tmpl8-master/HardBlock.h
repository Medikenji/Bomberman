#pragma once
#include "Entity.h"

class HardBlock : public Entity
{
public:
	HardBlock(float2 _blockPosition);
	~HardBlock() {};

private:
	// Functions
	void Update(float _deltaTime);


	// Variables
	static Surface m_texture;
};

