#pragma once
#include "Entity.h"

class HardBlock : public Entity
{
public:
	HardBlock(Position setposition);
	~HardBlock();

	// Functions
	void Update(float deltaTime);

private:
	Surface* texture;
};

