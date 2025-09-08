#pragma once
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
	static void SetSurface(Surface* a_Surface) { surface = a_Surface; }
	static Surface* surface;
	virtual void Update(float deltaTime) = 0;
	void UpdateChildren(float deltaTime);
	void AddChild(Entity* child);
	void DeleteChild(Entity* child);
	Entity *getChild(int index) { return m_children[index]; };
	Entity* getChildById(int ID);

	// Variables
	Sprite* sprite;
	Position position;
	Scale scale;
	
private:
	// Variables
	int childAmount;
	Entity* m_children[255];
	static int m_nextEntityId;
	int m_entityId;
};

