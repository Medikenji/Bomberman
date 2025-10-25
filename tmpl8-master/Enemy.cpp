#include "precomp.h"
#include "Enemy.h"
#include "BomberMan.h"
#include "Collision.h"

Enemy::Enemy()
{
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
	m_container->DeleteEntity(this);
}