#pragma once
#include "Entity.h"

class EndScreen : public Entity
{
public:
		EndScreen();
		~EndScreen();

		// Functions
		void Update(float _deltaTime);
};

