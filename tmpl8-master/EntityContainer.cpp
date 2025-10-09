#include "precomp.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "World.h"


EntityContainer::EntityContainer()
{
	m_nextEntityId = 0;
	m_entityAmount = 0;
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		surfaces[i] = new SplitSurface();
		surfaces[i]->surface = new Surface(RNDRWIDTH / m_surfaceAmount, RNDRHEIGHT);
		surfaces[i]->offsetX = 0;
		surfaces[i]->offsetY = 0;
	}
}


EntityContainer::~EntityContainer()
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		delete surfaces[i];
	}
	for (int i = 0; i < m_entityAmount; i++)
	{
		delete m_entities[i];
	}
}


void EntityContainer::SetSurfaceAmount(int _amount)
{
	if (m_surfaceAmount == -1)
	{
		m_surfaceAmount = _amount;
	}
}


void EntityContainer::UpdateEntities(float _deltaTime)
{
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (!m_entities[i]->isLiving)
			m_entities[i]->Update(_deltaTime);
	}
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->isLiving)
			m_entities[i]->Update(_deltaTime);
	}
}


void EntityContainer::AddEntity(Entity* _entityToAdd)
{
	_entityToAdd->SetEntityID(m_nextEntityId++);
	_entityToAdd->SetContainer(this);
	m_entities[m_entityAmount++] = _entityToAdd;
	_entityToAdd->Initialize();
}


void EntityContainer::DeleteEntity(Entity* _entityToDelete)
{
	int id = _entityToDelete->GetID();
	int childIndex = -1;
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->GetID() == _entityToDelete->GetID())
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


Entity* EntityContainer::GetEntityById(int _entityID) const
{
	for (int i = 0; i < m_entityAmount; i++)
	{
		if (m_entities[i]->GetID() == _entityID)
		{
			return m_entities[i];
		}
	}
	return nullptr;
}


void EntityContainer::SetCameraX(int _targetScreen, int _offsetX)
{
	int offsetX = _offsetX;
	if (offsetX > 0)
	{
		offsetX = 0;
	}
	int a = (Level::MAP_WIDTH - ((RNDRWIDTH / m_surfaceAmount) >> 4));
	int b = (a * World::BLOCKSIZE) - World::BLOCKSIZE;
	if (offsetX < -a - b + (m_surfaceAmount == 1 ? -8 : 0))
	{
		offsetX = -a - b + (m_surfaceAmount == 1 ? -8 : 0);
	}
	surfaces[_targetScreen]->offsetX = (float)offsetX;
}


void EntityContainer::DrawSplitScreens()const
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		surfaces[i]->surface->CopyTo(m_mainsurface, (RNDRWIDTH / m_surfaceAmount) * i, 0);
	}
}


void EntityContainer::ClearSurfaces(int _clearColor)
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		surfaces[i]->surface->Clear(_clearColor);
	}
}


void EntityContainer::CopyToSurfaces(Surface* _surface, float2 _position)
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		_surface->CopyTo(surfaces[i]->surface, (int)(_position.x + surfaces[i]->offsetX), (int)(_position.y + surfaces[i]->offsetY));
	}
}


void EntityContainer::DrawToSurfaces(Sprite* _sprite, float2 _position)
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		_sprite->Draw(surfaces[i]->surface, (int)(_position.x + surfaces[i]->offsetX), (int)(_position.y + surfaces[i]->offsetY));
	}
}


void EntityContainer::PlotToSurfaces(int _pixelColor, float2 _position)
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		surfaces[i]->surface->Plot((int)(_position.x + surfaces[i]->offsetX), (int)(_position.y + surfaces[i]->offsetY), _pixelColor);
	}
}


void EntityContainer::BoxToSurfaces(int _pixelColor, float4 _rectangle)
{
	for (int i = 0; i < m_surfaceAmount; i++)
	{
		surfaces[i]->surface->Box(
			(int)(_rectangle.x + surfaces[i]->offsetX),
			(int)(_rectangle.y + surfaces[i]->offsetY),
			(int)(_rectangle.x + _rectangle.w + surfaces[i]->offsetX),
			(int)(_rectangle.y + _rectangle.z + surfaces[i]->offsetY),
			_pixelColor);
	}
}