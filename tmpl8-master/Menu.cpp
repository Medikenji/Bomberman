#include "precomp.h"
#include "Menu.h"
#include "game.h"
#include "SceneManager.h"
#include "BomberMan.h"
#include "AudioManager.h"

Menu::Menu()
{
	m_backGround = new Surface("assets/MenuScreen.png");
	m_arrow = new Surface("assets/Arrow.png");
	choice = 0;
	previousChoice = choice;
	AudioManager::GetAudioManager()->PlayAudio(Audio::MenuSong);
}


Menu::~Menu()
{
	delete m_backGround;
	delete m_arrow;
}


void Menu::Update(float)
{
	m_backGround->CopyTo(container->GetSurface(), static_cast<int>(position.x), static_cast<int>(position.y));

	if (GetAsyncKeyState(GLFW_KEY_1) || GetAsyncKeyState(GLFW_KEY_KP_0))
	{
		if (previousChoice != 0)
		{
			choice = 0;
			AudioManager::GetAudioManager()->PlayAudio(Audio::MenuSelect);
		}
	}
	if (GetAsyncKeyState(GLFW_KEY_2) || GetAsyncKeyState(GLFW_KEY_KP_2))
	{
		if (previousChoice != 1)
		{
			choice = 1;
			AudioManager::GetAudioManager()->PlayAudio(Audio::MenuSelect);
		}
	}
	if (GetAsyncKeyState(GLFW_KEY_3) || GetAsyncKeyState(GLFW_KEY_KP_3))
	{
		if (previousChoice != 2)
		{
			choice = 2;
			AudioManager::GetAudioManager()->PlayAudio(Audio::MenuSelect);
		}
	}

	if (GetAsyncKeyState(GLFW_KEY_SPACE) && choice == 0)
	{
		AudioManager::GetAudioManager()->StopAudio(Audio::MenuSong);
		EntityContainer::SetSurfaceAmount(1);
		BomberMan** players = new BomberMan*[1];;
		for (int i = 0; i < 1; i++)	
		{
			players[i] = new BomberMan(i);
		}
		BomberMan::SetPlayers(players, 1);
		container->GetSceneManager()->ChangeScene(1);
	}

	if (GetAsyncKeyState(GLFW_KEY_SPACE) && choice == 1)
	{
		Game::CloseProgram();
	}

	if (GetAsyncKeyState(GLFW_KEY_SPACE) && choice == 2)
	{
		AudioManager::GetAudioManager()->StopAudio(Audio::MenuSong);
		EntityContainer::SetSurfaceAmount(2);
		BomberMan** players = new BomberMan*[2];;
		for (int i = 0; i < 2; i++)
		{
			players[i] = new BomberMan(i);
		}
		BomberMan::SetPlayers(players, 2);
		container->GetSceneManager()->ChangeScene(1);
	}
	previousChoice = choice;
	m_arrow->CopyTo(container->GetSurface(), static_cast<int>(position.x + ARROW_POSITIONS[choice].x), static_cast<int>(position.y + ARROW_POSITIONS[choice].y));
}