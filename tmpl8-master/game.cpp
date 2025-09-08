// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

void Game::Init()
{
	ActorPool::ActorPool();
	ActorPool::Add(world = new World());
	ActorPool::Add(bomber = new BomberMan());
	Actor::SetSurface(screen);
	
}

void Game::Tick(float deltaTime)
{
	screen->Clear(0xbdbebd);
	ActorPool::Tick(deltaTime);
	world->GetCurrentBlock(bomber->x, bomber->y);
	// fps counter
	//printf("dt: %i \n", (int)(1/deltaTime));
}