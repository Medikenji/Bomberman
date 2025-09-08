#include "precomp.h"
#include "Entity.h"

Surface* Entity::surface;
int Entity::m_nextEntityId = 0;

Entity::Entity()
{
	m_entityId = m_nextEntityId++;
	position.x = 0, position.y = 0;
	scale.x = 1, scale.y = 1;
	childAmount = 0;
}

Entity::~Entity()
{
	for (int i = 0; i < childAmount; i++)
	{
		m_children[i]->DeleteChild(m_children[i]);
	}
}

void Entity::UpdateChildren(float deltaTime)
{
	for (int i = 0; i <childAmount; i++)
	{
		m_children[i]->Update(deltaTime);
		m_children[i]->UpdateChildren(deltaTime);
	}
}

void Entity::AddChild(Entity* child)
{
	m_children[childAmount++] = child;
}

void Entity::DeleteChild(Entity* child)
{
	int id = child->m_entityId;
	int childIndex = -1;
	for (int i = 0; i < childAmount; i++)
	{
		if (m_children[i]->m_entityId == child->m_entityId)
		{
			childIndex = i;
			delete m_children[i];
			break;
		}
	}
	if (childIndex == -1)
	{
		std::cout << "Did not find child to delete with ID: " << id << "\n";
		return;
	}
	for (int i = childIndex + 1; i < childAmount - childIndex; i++)
	{
		m_children[i - 1] = m_children[i];
	}
	childAmount--;
}

Entity* Entity::getChildById(int id)
{
	for (int i = 0; i < childAmount; i++)
	{
		if (m_children[i]->m_entityId == id)
		{
			return m_children[i];
		}
	}
}