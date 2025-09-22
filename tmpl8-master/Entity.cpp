#include "precomp.h"
#include "Entity.h"
#include "World.h"

Surface* Entity::mainsurface;
Entity::SplitSurface* Entity::surfaces[SURFACEAMOUNT];
Entity* Entity::m_entities[1024];
bool Entity::m_initialisedSurfaces = false;
int Entity::m_nextEntityId = 0;
int Entity::m_entityAmount = 0;

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
	isLiving = 0;
	m_entityId = m_nextEntityId++;
	position.x = 0, position.y = 0;
	scale.x = 1, scale.y = 1;
}

Entity::~Entity()
{

}

void Entity::UpdateEntities(float deltaTime)
{
	for (int i = 0; i < m_entityAmount; i++)
	{
		if(!m_entities[i]->isLiving)
		m_entities[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->isLiving)
		m_entities[i]->Update(deltaTime);
	}
}

void Entity::AddEntity(Entity* child)
{
	m_entities[m_entityAmount++] = child;
	child->Initialise();
}

void Entity::DeleteEntity(Entity* child)
{
	int id = child->m_entityId;
	int childIndex = -1;
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->m_entityId == child->m_entityId)
		{
			childIndex = i;
			delete m_entities[i];
			break;
		}
	}
	if (childIndex == -1)
	{
		std::cout << "Did not find child to delete with ID: " << id << "\n";
		return;
	}
	for (int i = childIndex + 1; i < m_entityAmount; i++)
	{
		m_entities[i - 1] = m_entities[i];
	}
	m_entityAmount--;
}


Entity* Entity::GetEntityById(int id)
{
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->m_entityId == id)
		{
			return m_entities[i];
		}
	}
	return nullptr;
}

void Entity::SetCameraX(int screen, int x)
{
	if (x > 0)
	{
		x = 0;
	}
	int a = (World::currentLevel->getMapWidth() - ((RNDRWIDTH / SURFACEAMOUNT) >> 4));
	int b = (a * World::BLOCKSIZE) - World::BLOCKSIZE;
	if (x < -a-b+(SURFACEAMOUNT==1?-8:0))
	{
		x = -a-b+(SURFACEAMOUNT==1?-8:0);
	}
	surfaces[screen]->offsetX = x;
}

void Entity::drawSplitScreens()
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		surfaces[i]->surface->CopyTo(mainsurface, (RNDRWIDTH/SURFACEAMOUNT) * i, 0);
	}
}

void Entity::CopyToSurfaces(Surface* srfc, int x, int y)
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		srfc->CopyTo(surfaces[i]->surface, x + surfaces[i]->offsetX, y + surfaces[i]->offsetY);
	}
}

void Entity::DrawToSurfaces(Sprite* sprt, int x, int y)
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		sprt->Draw(surfaces[i]->surface, x + surfaces[i]->offsetX, y + surfaces[i]->offsetY);
	}
}

void Entity::PlotToSurfaces(int x, int y, int color)
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		surfaces[i]->surface->Plot(x + surfaces[i]->offsetX, y + surfaces[i]->offsetY, color);
	}
}

void Entity::ClearSurfaces()
{
	for (int i = 0; i < SURFACEAMOUNT; i++)
	{
		surfaces[i]->surface->Clear(0xbdbebd);
	}
}