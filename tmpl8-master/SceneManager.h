#pragma once
#include "EntityContainer.h"

class EntityContainer;
class World;

// Structs
class Scene
{
public:
	~Scene();
	EntityContainer* container = nullptr;
	bool splitscreen = 0;
	int clearColor = 0x000000;
};

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
	void ResetGame() {		m_reset = 1;	};
	void CleanUp();
	static World* GetCurrentWorld() { return m_currentWorld; };

private:
	// Functions
	static World* SetCurrentWorld(World* _world) { m_currentWorld = _world; return m_currentWorld; };

	// Variables
	const static int MAX_SCENES = 16;
	bool SwitchScene(uint_fast8_t _scene);
	bool m_reset;
	Surface* m_screen = nullptr;
	Scene* m_scenes[MAX_SCENES] = { nullptr };
	inline static World* m_currentWorld = nullptr;
	uint_fast8_t m_currentScene;
};

