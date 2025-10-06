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
	const static int MAX_SCENES = 16;
	void SwitchScene(UINT8 _scene);
	Surface* m_screen = nullptr;
	Scene* m_scenes[MAX_SCENES] = { nullptr };
	UINT8 m_currentScene;
};

