#include "precomp.h"
#include "Playership.h"

Playership::Playership()
{
	m_Sprite = new Sprite(new Surface("assets/playership.png"), 9);
	death = new Sprite(new Surface("assets/death.png"), 10);
	x = 10, y = 300, vx = vy = 0, btimer = 5, dtimer = 0;
}

bool Playership::Tick()
{
	int hor = 0, ver = 0;
	if (dtimer)
	{
		death->SetFrame(9 - (dtimer >> 4));
		death->Draw(surface, (int)x - 25, (int)y - 20);
		if (!--dtimer) x = 10, y = 300, vx = vy = 0;
		return true;
	}
	if (btimer) btimer--;
	if (GetAsyncKeyState(VK_UP)) vy = -1.7f, ver = 3;
	else if (GetAsyncKeyState(VK_DOWN)) vy = 1.7f, ver = 6;
	else { vy *= .97f, vy = (fabs(vy) < .05f) ? 0 : vy; }
	if (GetAsyncKeyState(VK_LEFT)) vx = -1.3f, hor = 0;
	else if (GetAsyncKeyState(VK_RIGHT)) vx = 1.3f, hor = 1;
	else { vx *= .97f, vx = (fabs(vx) < .05f) ? 0 : vx; }
	x = max(4.0f, min(SCRWIDTH - 140.0f, x + vx));
	y = max(4.0f, min(SCRHEIGHT - 40.0f, y + vy));
	m_Sprite->SetFrame(2 - hor + ver);
	m_Sprite->Draw(surface, (int)x, (int)y);
	for (unsigned short i = 2; i < ActorPool::actors; i++)
	{
		Actor* a = ActorPool::pool[i];
		if (a->GetType() == Actor::BULLET) if (((Bullet*)a)->owner == Bullet::ENEMY)
		{
			float dx = a->x - (x + 20), dy = a->y - (y + 12);
			if (sqrtf(dx * dx + dy * dy) < 15) dtimer = 159;
		}
		if (a->GetType() == Actor::ENEMY)
		{
			float dx = (a->x + 16) - (x + 20), dy = (a->y + 10) - (y + 12);
			if (sqrtf(dx * dx + dy * dy) < 18) dtimer = 159;
		}
		if (a->GetType() != Actor::METALBALL) continue;
		float dx = (a->x + 25) - (x + 20), dy = (a->y + 25) - (y + 12);
		if (sqrtf(dx * dx + dy * dy) < 35) dtimer = 159;
	}
	if ((!GetAsyncKeyState(VK_CONTROL)) || (btimer > 0)) return true;
	Bullet* newbullet = new Bullet();
	newbullet->Init(surface, x + 20, y + 18, 1, 0, Bullet::PLAYER);
	ActorPool::Add(newbullet);
	btimer = 15;
	return true;
}