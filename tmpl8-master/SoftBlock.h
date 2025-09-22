#pragma once
#include "Entity.h"
class SoftBlock : public Entity
{
public:
	SoftBlock(float2 setposition);
	~SoftBlock();

	// Functions
	void Update(float deltaTime);

private:
	static Sprite* m_sprite;
};

