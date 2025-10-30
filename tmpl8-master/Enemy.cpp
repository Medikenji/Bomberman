#include "precomp.h"
#include "Enemy.h"
#include "BomberMan.h"
#include "World.h"
#include "Collision.h"

Enemy::Enemy()
{
	m_score = UINT16_MAX;
	drawnOnTopLayer = 1;
	scale = 15;
}


void Enemy::PlayerCollision()
{
	for (int i = 0; i < BomberMan::GetPlayerAmount(); i++)
	{
		if (Collision::PixelPerfectCollision(this, BomberMan::GetPlayers()[i]))
			BomberMan::GetPlayers()[i]->Die();
	}
}


void Enemy::GoDie()
{
	m_currentWorld->AddScore(m_score);
	m_container->DeleteEntity(this);
}