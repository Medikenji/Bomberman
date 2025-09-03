#include "precomp.h"
#include "Map.h"
	
Surface* Actor::surface;

Map::Map()
{
	this->m_Sprite = new Sprite(new Surface("assets/HardBlocks.png"), 1);
};

bool Map::Tick()
{
	m_Sprite->Draw(surface, 20,20);
	return true;
}