#include "precomp.h"
#include "DeathScreen.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "FontRenderer.h"

DeathScreen::DeathScreen()
{
	m_surface = new Surface("assets/DeathScreen.png");
	m_resetTimer = 5.0f;
	AudioManager::GetAudioManager()->PlayAudio(Audio::DeathSound);
}


DeathScreen::~DeathScreen()
{
	delete m_surface;
}


void DeathScreen::Update(float _deltaTime)
{
	m_surface->CopyTo(m_container->GetSurface(), (int)(position.x), (int)(position.y));
	m_resetTimer -= _deltaTime;
	if (m_resetTimer < 0)
	{
		m_container->GetSceneManager()->ResetGame();
	}
	FontRenderer::DrawText({ 8,8}, (int)m_resetTimer+1, m_container);
}