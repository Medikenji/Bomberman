#include "precomp.h"
#include "SceneManager.h"
#include "Menu.h"
#include "World.h"
#include "DeathScreen.h"
#include "AudioManager.h"

SceneManager::SceneManager(Surface* _screen)
{
	m_screen = _screen;
	SwitchScene(0);
}


SceneManager::~SceneManager()
{
	AudioManager::DestroyAudioManager();
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (!m_scenes[i])
			continue;
		delete m_scenes[i];
	}
}


void SceneManager::Run(float _deltaTime)
{
	EntityContainer* container = m_scenes[m_currentScene]->container;
	container->ClearSurfaces(m_scenes[m_currentScene]->clearColor);
	container->UpdateEntities(_deltaTime);
	container = m_scenes[m_currentScene]->container;
	if (m_scenes[m_currentScene]->splitscreen)
	{
		container->DrawSplitScreens();
	}
}


void SceneManager::ChangeScene(uint_fast8_t _scene)
{
	uint_fast8_t currentScene = m_currentScene;
	if (!SwitchScene(_scene))
	{
		printf("Could not switch scene\n");
		SwitchScene(currentScene);
	}
}


void SceneManager::NextScene()
{
	uint_fast8_t currentScene = m_currentScene;
	if (!SwitchScene(m_currentScene+1))
	{
		printf("Could not switch scene\n");
		SwitchScene(currentScene);
	}
}


void SceneManager::PreviousScene()
{
	uint_fast8_t currentScene = m_currentScene;
	if (!SwitchScene(m_currentScene - 1))
	{
		printf("Could not switch scene\n");
		SwitchScene(currentScene);
	}
}


bool SceneManager::SwitchScene(uint_fast8_t _scene)
{
	Scene* newScene = nullptr;
	switch (_scene)
	{
	case 0:
		m_currentScene = _scene;
		if (m_scenes[_scene] != nullptr)
		{
			return 1;
		}
		newScene = new Scene();
		newScene->container = new EntityContainer();
		newScene->splitscreen = 0;
		newScene->container->AddEntity(new Menu());
		newScene->container->SetSurface(m_screen);
		newScene->container->SetSceneManager(this);
		newScene->clearColor = 0x000000;
		m_scenes[_scene] = newScene;
		return 1;
	case 1:
		m_currentScene = _scene;
		if (m_scenes[_scene] != nullptr)
		{
			return 1;
		}
		newScene = new Scene();
		newScene->container = new EntityContainer();
		newScene->splitscreen = 1;
		newScene->container->AddEntity(SetCurrentWorld(new World(new EnemyList(6, 0))));
		newScene->container->SetSurface(m_screen);
		newScene->container->SetSceneManager(this);
		newScene->clearColor = 0xbdbebd;
		m_scenes[_scene] = newScene;
		return 1;
	case 2:
		m_currentScene = _scene;
		if (m_scenes[_scene] != nullptr)
		{
			return 1;
		}
		newScene = new Scene();
		newScene->container = new EntityContainer();
		newScene->splitscreen = 1;
		newScene->container->AddEntity(SetCurrentWorld(new World(new EnemyList(3, 3))));
		newScene->container->SetSurface(m_screen);
		newScene->container->SetSceneManager(this);
		newScene->clearColor = 0xbdbebd;
		m_scenes[_scene] = newScene;
		return 1;
	case 15:
		m_currentScene = _scene;
		if (m_scenes[_scene] != nullptr)
		{
			return 1;
		}
		newScene = new Scene();
		newScene->container = new EntityContainer();
		newScene->container->AddEntity(new DeathScreen());
		newScene->container->SetSurface(m_screen);
		newScene->container->SetSceneManager(this);
		newScene->clearColor = 0x000000;
		m_scenes[_scene] = newScene;
		return 1;
	}
	return 0;
}