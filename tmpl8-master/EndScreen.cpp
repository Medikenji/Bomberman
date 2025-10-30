#include "precomp.h"
#include "EndScreen.h"
#include "AudioManager.h"

EndScreen::EndScreen()
{
	m_surface = new Surface("assets/Victory.png");
	AudioManager::GetAudioManager()->PlayAudio(Audio::VictoryTheme);
}


EndScreen::~EndScreen()
{
	delete m_surface;
}


void EndScreen::Update(float)
{
	m_surface->CopyTo(m_container->GetSurface(), (int)(position.x), (int)(position.y));
}