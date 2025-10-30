#pragma once

#define MAX_ENTITIES 2048

class Entity;
class SceneManager;

class EntityContainer
{
public:
	EntityContainer();
	~EntityContainer();


	// Structs
	struct SplitSurface
	{
		~SplitSurface()
		{
			delete surface;
		}
		// Variables
		Surface* surface = nullptr;
		float offsetX = 0, offsetY = 0;
	};

	// Functions
	void SetSurface(Surface* _surface) { m_mainsurface = _surface; }
	void SetSceneManager(SceneManager* _sceneManager) { m_sceneManager = _sceneManager; }
	Surface* GetSurface() const { return m_mainsurface; };
	static int GetSurfaceAmount() { return m_surfaceAmount; };
	static void SetSurfaceAmount(int _amount);
	SceneManager* GetSceneManager() const { return m_sceneManager; };
	void UpdateEntities(float _deltaTime);
	void AddEntity(Entity* _entityToAdd);
	void DeleteEntity(Entity* _entityToDelete);
	Entity* GetEntityById(int _entityID) const;
	void SetCameraX(int _targetScreen, int _offsetX);
	void DrawSplitScreens()const;
	void ClearSurfaces(int _clearColor);
	void CopyToSurfaces(Surface* _surface, float2 _position);
	void DrawToSurfaces(Sprite* _sprite, float2 _position, Entity* _entity);
	void DrawSpriteToScreen(Sprite* _sprite, float2 _position, uint_fast8_t _screen = 0);
	void PlotToSurfaces(int _pixelColor, float2 _position);
	void BoxToSurfaces(int _pixelColor, float4 _rectangle);

private:
	// Variables
	Surface* m_mainsurface = nullptr;
	SceneManager* m_sceneManager = nullptr;
	SplitSurface* surfaces[2]{ 0 };
	Entity** m_entities;
	inline static int m_surfaceAmount = -1;
	uint_least16_t m_nextEntityId;
	uint_least16_t m_entityAmount;
};

