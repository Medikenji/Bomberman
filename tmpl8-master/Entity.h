#pragma once

#define SURFACEAMOUNT 1
#define MAX_ENTITIES 1024


class Entity
{
public:
	Entity();

	// Enums
	enum {
		HARDWALL = 1,
		GRASS = 2,
		SOFTWALL = 3,
		BOMB = 4
	};

	// Functions
	virtual void Update(float deltaTime) = 0;
	static void SetSurface(Surface* a_Surface) { m_mainsurface = a_Surface; }
	static void DrawSplitScreens();
	static void ClearSurfaces();
	static void UpdateEntities(float deltaTime);
	static void AddEntity(Entity* child);
	static void DeleteEntity(Entity* child);
	int GetID() const { return m_entityId; };
	Entity* GetChild(int index) const { return m_entities[index]; };
	Entity* GetEntityById(int ID);
	float4 GetRectangle() const { return { position.x, scale.x, position.y, scale.y }; };

	// Variables
	float2 position;
	float2 scale;

protected:
	// Structs
	struct SplitSurface
	{
		// Variables
		Surface* surface = new Surface();
		float offsetX, offsetY;
	};

	// Functions
	static void SetCameraX(int screen, int x);
	void CopyToSurfaces(Surface* srfc, int x, int y);
	void DrawToSurfaces(Sprite* sprt, int x, int y);
	void PlotToSurfaces(int x, int y, int color);
	virtual void Initialise() {};

	// Variables
	static SplitSurface* surfaces[SURFACEAMOUNT];
	Sprite* sprite;
	bool isLiving;


private:
	// Variables
	static Surface* m_mainsurface;
	static int m_entityAmount;
	static Entity* m_entities[MAX_ENTITIES];
	static int m_nextEntityId;
	static bool m_initialisedSurfaces;
	int m_entityId;
};

