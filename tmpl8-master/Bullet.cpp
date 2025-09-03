#include "precomp.h"
#include "Bullet.h"

Bullet::Bullet()
{
	player = new Sprite(new Surface("assets/playerbullet.png"), 1);
	enemy = new Sprite(new Surface("assets/enemybullet.png"), 1);
}

Bullet::~Bullet()
{
	delete player;
	delete enemy;
}

bool Bullet::Tick()
{
	for (int i = 0; i < 4; i++)
	{
		x += 1.6f * vx, y += 1.6f * vy;
		if (owner == Bullet::PLAYER) player->Draw(surface, (int)x, (int)y);
		if (owner == Bullet::ENEMY) enemy->Draw(surface, (int)x, (int)y);
		if ((!--life) || (x > SCRWIDTH) || (x < 0) || (y < 0) || (y > SCRHEIGHT))
		{
			ActorPool::Delete(this);
			return false;
		}
		float nx, ny, vx_ = vx, vy_ = vy;
		if (!ActorPool::CheckHit(x, y, nx, ny)) continue;
		m_Spark->Draw(surface, (int)x - 4, (int)y - 4);
		x += (vx = -2 * (nx * vx_ + ny * vy_) * nx + vx_);
		y += (vy = -2 * (nx * vx_ + ny * vy_) * ny + vy_);
	}
	return true;
}