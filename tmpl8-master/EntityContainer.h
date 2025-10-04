#pragma once
#include "EntityContainer.h"

#define SURFACEAMOUNT 1
#define MAX_ENTITIES 20480

class Entity;

class EntityContainer
{
public:
	EntityContainer();

	Entity* GetChild(int _entityIndex) const { return m_entities[_entityIndex]; };

	// Structs
	struct SplitSurface
	{
		// Variables
		Surface* surface = new Surface();
		float offsetX = 0, offsetY = 0;
	};

	void SetSurface(Surface* _surface) { m_mainsurface = _surface; }
	void UpdateEntities(float _deltaTime);
	void AddEntity(Entity* _entityToAdd);
	void DeleteEntity(Entity* _entityToDelete);
	Entity* GetEntityById(int _entityID) const;
	void SetCameraX(int _targetScreen, int _offsetX);
	void DrawSplitScreens()const;
	void ClearSurfaces(int _clearColor);
	void CopyToSurfaces(Surface* _surface, float2 _position);
	void DrawToSurfaces(Sprite* _sprite, float2 _position);
	void PlotToSurfaces(int _pixelColor, float2 _position);

	Surface* m_mainsurface = nullptr;
	SplitSurface* surfaces[SURFACEAMOUNT]{ 0 };
	Entity* m_entities[MAX_ENTITIES]{ 0 };
	UINT16 m_nextEntityId;
	UINT16 m_entityAmount;
};

