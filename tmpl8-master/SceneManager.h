#pragma once
#include "EntityContainer.h"

class EntityContainer;
class World;

class SceneManager
{
public:
	SceneManager(Surface* _screen);
	~SceneManager();

	// Functions
	void Run(float _deltaTime);
	void ChangeScene(uint_fast8_t _scene);
	void NextScene();
	void PreviousScene();
	static World* GetCurrentWorld() { return m_currentWorld; };

private:
	// Functions
	static World* SetCurrentWorld(World* _world) { m_currentWorld = _world; return m_currentWorld; };

	// Structs
	struct Scene
	{
		~Scene() { delete container; };
		EntityContainer* container = nullptr;
		bool splitscreen = 0;
		int clearColor = 0x000000;
	};

	// Variables
	const static int MAX_SCENES = 16;
	bool SwitchScene(uint_fast8_t _scene);
	Surface* m_screen = nullptr;
	Scene* m_scenes[MAX_SCENES] = { nullptr };
	inline static World* m_currentWorld = nullptr;
	uint_fast8_t m_currentScene;
};

