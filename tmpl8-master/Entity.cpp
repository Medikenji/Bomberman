#include "precomp.h"
#include "Entity.h"

Surface* Entity::mainsurface;
Entity::SplitSurface* Entity::surfaces[SURFACEAMOUNT];
bool Entity::m_initialisedSurfaces = false;
int Entity::m_nextEntityId = 0;

Entity::Entity()
{
	if (!m_initialisedSurfaces)
	{
		for (int i = 0; i < SURFACEAMOUNT; i++)
		{
			surfaces[i] = new SplitSurface();
			surfaces[i]->surface = new Surface(RNDRWIDTH/SURFACEAMOUNT, RNDRHEIGHT);
			surfaces[i]->offsetX = 0;
			surfaces[i]->offsetY = 0;
		}
		m_initialisedSurfaces = true;
	}
	m_entityId = m_nextEntityId++;
	position.x = 0, position.y = 0;
	scale.x = 1, scale.y = 1;
	childAmount = -1;
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
	if (childAmount == 0)
		return;
	for (int i = 0; i < childAmount; i++)
	{
		m_children[i]->Update(deltaTime);
		m_children[i]->UpdateChildren(deltaTime);
	}
}

void Entity::AddChild(Entity* child)
{
	m_children[++childAmount] = child;
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
	return nullptr;
}

void Entity::drawSplitScreens()
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		surfaces[i]->surface->CopyTo(mainsurface, 128 * i, 0);
	}
}

void Entity::CopyToSurfaces(Surface* srfc, int x, int y)
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		srfc->CopyTo(surfaces[i]->surface, x + surfaces[i]->offsetX, y + surfaces[i]->offsetY);
	}
}

void Entity::DrawToSurfaces(Sprite* srfc, int x, int y)
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		srfc->Draw(surfaces[i]->surface, x + surfaces[i]->offsetX, y + surfaces[i]->offsetY);
	}
}