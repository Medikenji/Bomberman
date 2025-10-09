#include "precomp.h"
#include "DeathScreen.h"
#include "AudioManager.h"

DeathScreen::DeathScreen()
{
	AudioManager::StopAll();
	m_backGround = new Surface("assets/DeathScreen.png");
}


DeathScreen::~DeathScreen()
{

}


void DeathScreen::Update(float)
{
	m_backGround->CopyTo(container->GetSurface(), (int)(position.x), (int)(position.y));
}