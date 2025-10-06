#include "precomp.h"
#include "SceneManager.h"
#include "EntityContainer.h"
#include "World.h"

SceneManager::SceneManager(Surface* _screen)
{
	m_screen = _screen;
	SwitchScene(0);
}


SceneManager::~SceneManager()
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		delete m_scenes[i]->container;
		delete m_scenes[i];
	}
}


void SceneManager::Run(float _deltaTime)
{
	EntityContainer* container = m_scenes[m_currentScene]->container;
	container->ClearSurfaces(m_scenes[m_currentScene]->clearColor);
	container->UpdateEntities(_deltaTime);
	container->DrawSplitScreens();
}


void SceneManager::SwitchScene(UINT8 _scene)
{
	switch (_scene)
	{
	case 0:
		m_currentScene = _scene;
		if (m_scenes[_scene] != nullptr)
		{
			break;
		}
		Scene* newScene = new Scene();
		newScene->container = new EntityContainer();
		newScene->container->AddEntity(new World());
		newScene->container->SetSurface(m_screen);
		newScene->clearColor = 0xbdbebd;
		m_scenes[_scene] = newScene;
	}
}