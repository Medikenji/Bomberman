#include "precomp.h"
#include "HardBlock.h"

Surface HardBlock::m_texture{ ("assets/HardBlock.png") };

HardBlock::HardBlock(float2 _blockPosition)
{
	position = _blockPosition;
	// artificial width and height
	scale = { 16, 16 };
}


void HardBlock::Update(float)
{
	container->CopyToSurfaces(&m_texture, position);
}