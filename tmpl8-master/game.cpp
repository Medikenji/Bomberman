// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "SceneManager.h"

GLFWwindow* Game::m_window = nullptr;

void Game::Init()
{
	m_sceneManager = new SceneManager(screen);
}

void Game::Tick(float _deltaTime)
{
	m_sceneManager->Run(_deltaTime);
}

void Game::Shutdown()
{
	delete m_sceneManager;
}