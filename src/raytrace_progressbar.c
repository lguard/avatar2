#include "raytrace.h"

void	pbar2(t_scene *sc)
{
	if (sc->progressbar)
	{
		sc->progressbar = 0;
		print("\n");
	}
}

void	pbar(int x, int y, t_scene *sc)
{
	if (sc->progressbar)
	{
		print("\rprogress: %%%d       ",
		(int)(((FLOAT)(x * sc->height +y) /
		(FLOAT)(sc->height * sc->width)) * 100.f));
	}
}
