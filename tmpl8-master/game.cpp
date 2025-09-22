// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

void Game::Init()
{
	Entity::SetSurface(screen);
	Entity::AddEntity(new World());
}

void Game::Tick(float deltaTime)
{
	Entity::UpdateEntities(deltaTime);
	Entity::drawSplitScreens();
}