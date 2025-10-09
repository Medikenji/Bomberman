#pragma once
#include "EntityContainer.h"

class EntityContainer;

class Entity
{
public:
	Entity();
	virtual ~Entity() {};


	// Functions
	virtual void Update(float _deltaTime) = 0;
	virtual void Initialize() {};
	virtual void Die() {};
	int GetID() const { return m_entityId; };
	void SetEntityID(int _ID);
	void SetContainer(EntityContainer* _container);
	float4 GetRectangle() const { return { position.x, position.y, scale.x, scale.y }; };

	// Variables
	float2 position;
	float2 scale;
	bool isLiving;

protected:
	// Variables
	EntityContainer* container = nullptr;
	Sprite* sprite = nullptr;

private:
	// Variables
	int m_entityId;
};

