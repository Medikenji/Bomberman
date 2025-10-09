#pragma once
#include "Entity.h"

class Menu : public Entity
{
public:
	Menu();
	~Menu();

	// Functions
	void Update(float _deltaTime);

private:
	// Variables
	Surface* m_backGround = nullptr;
	Surface* m_arrow = nullptr;
	int choice;
	int previousChoice;
	inline static const float2 ARROW_POSITIONS[3] = { { 31.0f, 189.0f }, { 103.0f, 189.0f },{ 151.0f, 189.0f } };
};

