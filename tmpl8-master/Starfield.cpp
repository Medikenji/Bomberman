#include "precomp.h"
#include "Starfield.h"

Starfield::Starfield()
{
	x = new float[STARS], y = new float[STARS];
	for (short i = 0; i < STARS; i++) x[i] = Rand(SCRWIDTH), y[i] = Rand(SCRHEIGHT);
}

bool Starfield::Tick()
{
	for (short i = 0; i < STARS; i++)
	{
		if ((x[i] -= ((float)i + 1) / STARS) < 0) x[i] = SCRWIDTH;
		int color = 55 + (int)(((float)i / STARS) * 200.0f);
		surface->Plot((int)x[i], (int)y[i], color + (color << 8) + (color << 16));
	}
	return true;
}