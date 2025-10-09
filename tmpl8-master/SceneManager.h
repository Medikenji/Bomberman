#pragma once
#include "EntityContainer.h"

class EntityContainer;

class SceneManager
{
public:
	SceneManager(Surface* _screen);
	~SceneManager();

	// Functions
	void Run(float _deltaTime);
	bool ChangeScene(UINT8 _scene);

private:
	// Structs
	struct Scene
	{
		EntityContainer* container = nullptr;
		bool splitscreen = false;
		int clearColor = 0x000000;
	};

	// Variables
	const static int MAX_SCENES = 16;
	bool SwitchScene(UINT8 _scene);
	Surface* m_screen = nullptr;
	Scene* m_scenes[MAX_SCENES] = { nullptr };
	UINT8 m_currentScene;
};

