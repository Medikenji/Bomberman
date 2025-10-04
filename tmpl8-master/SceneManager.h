#pragma once

class EntityContainer;

class SceneManager
{
public:
	SceneManager(Surface* _screen);
	~SceneManager();

	void Run(float _deltaTime);

private:
	struct Scene
	{
		EntityContainer* container = nullptr;
		int clearColor = 0x000000;
	};

	void SwitchScene(int _scene);
	Surface* m_screen = nullptr;
	Scene* m_scenes[16] = { nullptr };
	UINT8 m_currentScene;
};

