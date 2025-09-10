#include "precomp.h"
#include "HardBlock.h"

HardBlock::HardBlock(Position setposition)
{
	position = setposition;
	// Const artificial width and height
	scale = { 16, 16 };
	texture = new Surface("assets/HardBlock.png");
}

HardBlock::~HardBlock()
{

}

void HardBlock::Update(float deltaTime)
{
	CopyToSurfaces(texture, position.x, position.y);
}