#include "precomp.h"
#include "SceneManager.h"
#include "Menu.h"
#include "World.h"
#include "DeathScreen.h"

SceneManager::SceneManager(Surface* _screen)
{
	m_screen = _screen;
	SwitchScene(0);
}


SceneManager::~SceneManager()
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (!m_scenes[i])
			break;
		delete m_scenes[i]->container;
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


bool SceneManager::ChangeScene(UINT8 _scene)
{
	UINT8 currentScene = m_currentScene;
	if (!SwitchScene(_scene))
	{
		printf("Could not switch scene\n");
		SwitchScene(currentScene);
		return false;
	}
	return true;
}


bool SceneManager::SwitchScene(UINT8 _scene)
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
		newScene->splitscreen = false;
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
		newScene->splitscreen = true;
		newScene->container->AddEntity(new World(new EnemyList(6, 0)));
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