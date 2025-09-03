#pragma once

#include "precomp.h"

class Actor
{
public:
	enum
	{
		UNDEFINED = 0,
		PLAYER = 1,
		HARDWALL = 2,
		SOFTWALL = 3,
		BOMB = 4
	};
	virtual bool Tick(float deltaTime) = 0;
	virtual bool Hit(float&, float&, float&, float&) { return false; }
	virtual int GetType() { return Actor::UNDEFINED; }
	static void SetSurface(Surface* a_Surface) { surface = a_Surface; }
	static Surface* surface;
	Sprite* m_Sprite;
	static Sprite* m_Spark;
	float x, y;
};