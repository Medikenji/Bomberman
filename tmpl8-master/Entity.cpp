#include "precomp.h"
#include "Entity.h"
#include "World.h"


Entity::Entity()
{
	m_entityId = NULL;
	isLiving = 0;
	position = 0;
	scale = 1;
}

void Entity::SetEntityID(int ID)
{
	if (m_entityId != NULL)
	{
		return;
	}

	m_entityId = ID;
}

void Entity::SetContainer(EntityContainer* _container)
{
	if (container != nullptr)
	{
		return;
	}

	container = _container;
}