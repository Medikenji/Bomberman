#pragma once
#include "Entity.h"

class HardBlock : public Entity
{
public:
	HardBlock(float2 setposition);
	~HardBlock();

	// Functions
	void Update(float deltaTime);

private:
	static Surface* m_texture;
};

