#include "precomp.h"
#include "DeathScreen.h"
#include "AudioManager.h"

DeathScreen::DeathScreen()
{
	AudioManager::StopAll();
  	m_surface = new Surface("assets/DeathScreen.png");
}


DeathScreen::~DeathScreen()
{
	delete m_surface;
}


void DeathScreen::Update(float)
{
	m_surface->CopyTo(m_container->GetSurface(), (int)(position.x), (int)(position.y));
}