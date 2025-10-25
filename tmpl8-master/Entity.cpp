#include "precomp.h"
#include "Entity.h"
#include "World.h"


Entity::Entity()
{
	m_entityId = 0;
	m_currentFrame = 0;
	drawnOnTopLayer = 0;
	position = 0;
	scale = 1;
	m_isDead = 0;
	m_maskWidth = 0;
	m_maskHeight = 0;
	m_maskFrames = 0;

}


void Entity::SetEntityID(int ID)
{
	if (m_entityId != 0)
	{
		return;
	}
	m_entityId = ID;
}


void Entity::SetContainer(EntityContainer* _container)
{
	m_container = _container;
}


bool* Entity::GetMask()
{
	int currentFrame = m_currentFrame;
	const int maskSize = m_maskWidth * m_maskHeight;
	bool* mask = new bool[maskSize<<1];

	for (int i = 0; i < m_maskHeight; i++) {
		for (int j = 0; j < m_maskWidth; j++) {
			int index = currentFrame * m_maskWidth * m_maskHeight + i * m_maskWidth + j;
			mask[i * m_maskWidth + j] = m_mask[index];
		}
	}
	return mask;
}


int2 Entity::GetMaskProportions()
{
	return { m_maskWidth, m_maskHeight };
}


void Entity::AddSprite(Sprite* _newSprite)
{
	m_sprite = _newSprite;
	const int width = m_sprite->GetWidth();
	const int height = m_sprite->GetHeight();
	const int frames = m_sprite->Frames();
	const uint* buffer = m_sprite->GetBuffer();
	m_maskWidth = width;
	m_maskHeight = height;
	m_maskFrames = frames;
	m_mask = new bool[m_maskWidth * m_maskHeight * m_maskFrames] {0};

	// Logic scraped from Sprite::Draw
	for (int f = 0; f < frames; f++)
	{
		const uint* src = buffer + f * width;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				const uint c1 = *(src + i);
				// Getting the right index was made with help from ChatGPT
				int index = f * width * height + j * width + i;
				if (c1 != 0xff00ff) m_mask[index] = 1;
			}
			src += width * frames;
		}
	}
}