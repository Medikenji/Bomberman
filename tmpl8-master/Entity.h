#pragma once

#define SURFACEAMOUNT 1

class Entity
{
public:
	Entity();
	~Entity();

	// Enums
	enum {
		GRASS = 0,
		HARDWALL = 1,
		SOFTWALL = 2,
		BOMB = 3
	};

	// Functions
	static void SetSurface(Surface* a_Surface) { mainsurface = a_Surface; }
	static Surface* mainsurface;
	static void ClearSurfaces();
	static void drawSplitScreens();
	virtual void Update(float deltaTime) = 0;
	static void UpdateEntities(float deltaTime);
	int GetID() { return m_entityId; };
	static void AddEntity(Entity* child);
	void DeleteEntity(Entity* child);
	Entity *GetChild(int index) { return m_entities[index]; };
	Entity* GetEntityById(int ID);
	float4 GetRectangle() { return { position.x, scale.x, position.y, scale.y }; };

	// Variables
	float2 position;
	float2 scale;
	
protected:
	// Structs
	struct SplitSurface
	{
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
	Sprite* sprite;
	static SplitSurface* surfaces[SURFACEAMOUNT];
	bool isLiving;


private:
	// Variables
	static int m_entityAmount;
	static Entity* m_entities[1024];
	static int m_nextEntityId;
	int m_entityId;
	static bool m_initialisedSurfaces;
};

