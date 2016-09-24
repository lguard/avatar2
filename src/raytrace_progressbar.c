#include "raytrace.h"

static char	*color_bar(int progress)
{
	if (progress > 87.5)
		return ("\x1b[38;5;46m");
	else if (progress > 75)
		return ("\x1b[38;5;34m");
	else if (progress > 62)
		return ("\x1b[38;5;70m");
	else if (progress > 50)
		return ("\x1b[38;5;106m");
	else if (progress > 37)
		return ("\x1b[38;5;142m");
	else if (progress > 25)
		return ("\x1b[38;5;202m");
	else if (progress > 12.5)
		return ("\x1b[38;5;196m");
	else
		return ("\x1b[38;5;88m");
}

void		pbar(int x, int y, t_scene *sc)
{
	int	progress;

	if (sc->progressbar)
	{
		progress = (int)(((FLOAT)(x * sc->height +y) /
		(FLOAT)(sc->height * sc->width)) * 100.f);
		print("\rprogress: %s%d%%\x1b[0m  ", color_bar(progress), progress);
	}
}


