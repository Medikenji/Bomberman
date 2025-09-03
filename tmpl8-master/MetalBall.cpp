#include "precomp.h"
#include "MetalBall.h"

MetalBall::MetalBall()
{
	m_Sprite = new Sprite(new Surface("assets/ball.png"), 1);
	while (1)
	{
		x = Rand(SCRWIDTH * 4) + SCRWIDTH * 1.2f, y = 10 + Rand(SCRHEIGHT - 70);
		bool hit = false;
		for (int i = 2; i < ActorPool::actors; i++)
		{
			MetalBall* b2 = (MetalBall*)ActorPool::pool[i];
			float dx = b2->x - x, dy = b2->y - y;
			if (sqrtf(dx * dx + dy * dy) < 100) hit = true;
		}
		if (!hit) break;
	}
}

bool MetalBall::Tick()
{
	if ((x -= .2f) < -50) x = SCRWIDTH * 4;
	m_Sprite->Draw(surface, (int)x, (int)y);
	for (char u = 0; u < 50; u++) for (char v = 0; v < 50; v++)
	{
		float tx = (float)(u + x), ty = (float)(v + y);
		if ((tx < 0) || (ty < 0) || (tx >= SCRWIDTH) || (ty >= SCRHEIGHT)) continue;
		uint* src1 = m_Sprite->GetBuffer() + u + v * 50;
		if (!(*src1 & 0xffffff)) continue;
		float dx = (float)(u - 25) / 25, dy = (float)(v - 25) / 25;
		float l = sqrtf(dx * dx + dy * dy) * .2f * PI;
		short sx = (int)(((x + 25) + (int)((160 * sin(l) + 100) * dx) + SCRWIDTH)) % SCRWIDTH;
		short sy = (int)(((y + 25) + (int)((160 * sin(l) + 100) * dy) + SCRHEIGHT)) % SCRHEIGHT;
		uint* src2 = surface->pixels + sx + sy * surface->width;
		uint* dst = surface->pixels + (int)tx + (int)ty * surface->width;
		*dst = AddBlend(*src1, *src2 & 0xffff00);
	}
	return true;
}

bool MetalBall::Hit(float& a_X, float& a_Y, float& a_NX, float& a_NY)
{
	float dist, dx = a_X - (x + 25), dy = a_Y - (y + 25);
	if ((dist = sqrtf(dx * dx + dy * dy)) > 25) return false;
	a_NX = (float)(dx / sqrtf(dx * dx + dy * dy)), a_NY = (float)(dy / sqrtf(dx * dx + dy * dy));
	a_X = (float)(x + 25 + (dx / sqrtf(dx * dx + dy * dy)) * 25.5f), a_Y = (float)(y + 25 + (dy / sqrtf(dx * dx + dy * dy)) * 25.5f);
	return true;
}