#pragma once
#include "Entity.h"

class HardBlock : public Entity
{
public:
	HardBlock(float2 setposition);

	// Functions
	void Update(float deltaTime);

private:
	// Variables
	static Surface* m_texture;
};

