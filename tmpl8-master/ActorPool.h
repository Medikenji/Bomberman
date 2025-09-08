#pragma once

#include "Actor.h"

#define MAXACTORS 1024

class ActorPool
	{
	public:
		ActorPool() { pool = new Actor * [MAXACTORS]; actors = 0; }
		static void Tick(float deltaTime)
		{
			for (int i = 0; i < actors; i++)
			{
				Actor* actor = pool[i];
				if (!actor->Tick(deltaTime)) delete actor;
			}
		}
		static void Add(Actor* a_Actor) { pool[actors++] = a_Actor; }
		static void Delete(Actor* actor)
		{
			for (int i = 0; i < actors; i++) if (pool[i] == actor)
			{
				for (int j = i + 1; j < actors; j++) pool[j - 1] = pool[j];
				actors--;
				break;
			}
		}
		static bool CheckHit(float& a_X, float& a_Y, float& a_NX, float& a_NY)
		{
			for (int i = 0; i < actors; i++)
				if (pool[i]->Hit(a_X, a_Y, a_NX, a_NY)) return true;
			return false;
		}
		static int GetActiveActors() { return actors; }
		static Actor** pool;
		static int actors;
	};