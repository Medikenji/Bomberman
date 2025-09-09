#pragma once

#define SURFACEAMOUNT 2

class Entity
{
public:
	Entity();
	~Entity();

	// Structs
	struct Position
	{
		float x, y;
	};
	struct Scale
	{
		float x, y;
	};

	// Functions
	static void SetSurface(Surface* a_Surface) { mainsurface = a_Surface; }
	static Surface* mainsurface;
	static void drawSplitScreens();
	virtual void Update(float deltaTime) = 0;
	void UpdateChildren(float deltaTime);
	void AddChild(Entity* child);
	void DeleteChild(Entity* child);
	Entity *getChild(int index) { return m_children[index]; };
	Entity* getChildById(int ID);

	// Variables
	Position position;
	Scale scale;
	
protected:
	// Structs
	struct SplitSurface
	{
		Surface* surface = new Surface();
		float offsetX, offsetY;
	};

	// Functions
	void CopyToSurfaces(Surface* srfc, int x, int y);
	void DrawToSurfaces(Sprite* srfc, int x, int y);

	// Variables
	Sprite* sprite;
	static SplitSurface* surfaces[SURFACEAMOUNT];


private:
	// Variables
	int childAmount;
	Entity* m_children[255];
	static int m_nextEntityId;
	int m_entityId;
	static bool m_initialisedSurfaces;
};

