#include "precomp.h"
#include "HardBlock.h"

Surface* HardBlock::m_texture = new Surface("assets/HardBlock.png");

HardBlock::HardBlock(float2 setposition)
{
	position = setposition;
	// artificial width and height
	scale = { 16, 16 };
}


void HardBlock::Update(float deltaTime)
{
	CopyToSurfaces(m_texture, position.x, position.y);
}