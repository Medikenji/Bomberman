#include "precomp.h"
#include "Enemy.h"

Enemy::Enemy()
{
	m_Sprite = new Sprite(new Surface("assets/enemy.png"), 4);
	death = new Sprite(new Surface("assets/edeath.png"), 4);
	vx = -1.4f, x = SCRWIDTH * 2 + Rand(SCRWIDTH * 4);
	vy = 0, y = SCRHEIGHT * .2f + Rand(SCRWIDTH * .6f);
	frame = 0, btimer = 5, dtimer = 0;
}

bool Enemy::Tick()
{
	if (dtimer)
	{
		death->SetFrame(3 - (dtimer >> 3));
		death->Draw(surface, (int)x - 1015, (int)y - 15);
		if (!--dtimer) x = SCRWIDTH * 3, y = Rand(SCRHEIGHT), vx = -1.4f, vy = 0;
		return true;
	}
	x += vx, y += (vy *= .99f), frame = (frame + 1) % 31;
	if (x < -50) x = SCRWIDTH * 4;
	m_Sprite->SetFrame(frame >> 3);
	m_Sprite->Draw(surface, (int)x, (int)y);
	for (int i = 0; i < ActorPool::actors; i++)
	{
		Actor* a = ActorPool::pool[i];
		if (a->GetType() == Actor::BULLET) if (((Bullet*)a)->owner == Bullet::PLAYER)
		{
			double dx = (x + 15) - a->x, dy = (y + 11) - a->y;
			if ((dx * dx + dy * dy) < 100)
			{
				dtimer = 31, x += 1000;
				ActorPool::Delete(a);
				delete a;
			}
		}
		double hdist = (x + 15) - (a->x + 25), vdist = (a->y + 25) - (y + 11);
		if (((hdist < 0) || (hdist > 120)) || (a->GetType() != Actor::METALBALL)) continue;
		if ((vdist > 0) && (vdist < 30)) vy -= (float)((121 - hdist) * .0015);
		if ((vdist < 0) && (vdist > -30)) vy += (float)((121 - hdist) * .0015);
	}
	if (y < 100) vy += .05f; else if (y > (SCRHEIGHT - 100)) vy -= .05f;
	Playership* p = (Playership*)ActorPool::pool[1];
	float dx = p->x - x, dy = p->y - y, dist = sqrtf(dx * dx + dy * dy);
	if ((dist > 180) || (dist < 100)) return true;
	vx += (float)((dx / 50.0) / dist), vy += (float)((dy / 50.0) / dist);
	if (--btimer) return true; else btimer = 19;
	Bullet* newbullet = new Bullet();
	newbullet->Init(surface, x + 15, y + 10, (float)((dx / 5.0f) / dist), (float)((dy / 5.0f) / dist), Bullet::ENEMY);
	ActorPool::Add(newbullet);
	return true;
}