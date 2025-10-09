#include "precomp.h"
#include "Enemy.h"
#include "BomberMan.h"
#include "Collision.h"

Enemy::Enemy()
{

}

void Enemy::PlayerCollision()
{
	for (int i = 0; i < BomberMan::GetPlayerAmount(); i++)
	{
		if (Collision::RecToRec(GetRectangle(), BomberMan::GetPlayers()[i]->GetRectangle()))
			BomberMan::GetPlayers()[i]->Die();
	}
}

void Enemy::Die()
{
	container->DeleteEntity(this);
}