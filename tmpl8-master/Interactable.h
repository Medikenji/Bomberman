#pragma once
#include "Entity.h"
#include "SoftBlock.h"

class BomberMan;

class Interactable : public Entity
{
public:
	Interactable(float2 _blockPosition, BlockContent _content);
	~Interactable();

private:
	// Functions
	void Update(float _deltaTime);
	virtual void Initialize();

	void Function();
	void Exit();
	void Skate(BomberMan* _pl0ayer);
	void Fire(BomberMan* _player);


	Surface* m_surface = nullptr;
	World* m_currentWorld = nullptr;
	BlockContent m_content;
};