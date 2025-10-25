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
	void Die() { m_isDead = 1; };
	bool IsDead()const { return m_isDead; };
	/// <summary>WARNING: please ensure the pointer that is returned gets deleted somewhere</summary>
	bool* GetMask();
	int2 GetMaskProportions();
	void DeleteMask() { delete[] m_mask; };
	int GetID() const { return m_entityId; };
	uint_fast8_t GetCurrentFrame() const { return m_currentFrame; };
	void SetEntityID(int _ID);
	void SetContainer(EntityContainer* _container);
	float4 GetRectangle() const { return { position.x, position.y, scale.x, scale.y }; };

	// Variables
	float2 position;
	float2 scale;
	bool drawnOnTopLayer;

protected:
	// Variables
	/// <summary>Sets m_sprite while also making a mask for the sprite</summary>
	void AddSprite(Sprite* _newSprite);
	EntityContainer* m_container = nullptr;
	Surface* m_surface = nullptr;
	Sprite* m_sprite = nullptr;
	bool m_isDead;
	uint_fast8_t m_currentFrame;


private:
	// Variables
	bool* m_mask = nullptr;
	int m_maskWidth, m_maskHeight, m_maskFrames;
	int m_entityId;
};

