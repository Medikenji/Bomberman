// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

void Game::Init()
{
	ActorPool::ActorPool();
	ActorPool::Add(new Starfield());
	ActorPool::Add(new Playership());
	for (char i = 0; i < 50; i++) ActorPool::Add(new MetalBall());
	for (char i = 0; i < 20; i++) ActorPool::Add(new Enemy());
	Actor::SetSurface(screen);
	Actor::m_Spark = new Sprite(new Surface("assets/hit.png"), 1);
	// Actor::m_Spark->SetFlags( Sprite::FLARE );
}

void Game::DrawBackdrop()
{
	for (int i, y = 0; y < SCRHEIGHT; y += 4) for (int x = 0; x < SCRWIDTH; x += 4)
	{
		float sum1 = 0, sum2 = 0;
		for (i = 1; i < ActorPool::actors; i++)
		{
			Actor* a = ActorPool::pool[i];
			if (a->GetType() == Actor::ENEMY) break; else if (a->x > (x + 120)) continue;
			double dx = (a->x + 20) - x, dy = (a->y + 20) - y;
			sum1 += 100000.0f / (float)(dx * dx + dy * dy);
		}
		for (; i < ActorPool::actors; i++)
		{
			Actor* a = ActorPool::pool[i];
			if (a->GetType() == Actor::BULLET) break; else if (a->x > (x + 80)) continue;
			double dx = (a->x + 15) - x, dy = (a->y + 12) - y;
			sum2 += 70000.0f / (float)(dx * dx + dy * dy);
		}
		int color = (int)min(255.0f, sum1) + ((int)min(255.0f, sum2) << 16), p = SCRWIDTH;
		for (i = 0; i < 4; i++) screen->pixels[x + (i & 1) + (y + ((i >> 1) & 1)) * p] = color;
	}
}

void Game::Tick(float)
{
	screen->Clear(0);
	DrawBackdrop();
	ActorPool::Tick();
}