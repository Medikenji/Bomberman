#include "precomp.h"
#include "HardBlock.h"

HardBlock::HardBlock(float2 _blockPosition)
{
	m_surface = new Surface("assets/HardBlock.png");
	position = _blockPosition;
	// artificial width and height
	scale = { 16, 16 };
}


HardBlock::~HardBlock()
{
	delete m_surface;
}


void HardBlock::Update(float)
{
	m_container->CopyToSurfaces(m_surface, position);
}