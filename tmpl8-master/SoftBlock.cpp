#include "precomp.h"
#include "SoftBlock.h"

Sprite* SoftBlock::m_sprite = new Sprite(new Surface("assets/SoftBlock.png"),7);

SoftBlock::SoftBlock(float2 setposition)
{
	position = setposition;
	// artificial width and height
	scale = { 16, 16 };
}

SoftBlock::~SoftBlock()
{

}

void SoftBlock::Update(float deltaTime)
{
	DrawToSurfaces(m_sprite, position.x, position.y);
}