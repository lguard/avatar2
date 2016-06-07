#include "mysdl.h"

void	sdl_putpxl(t_env *e, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	SDL_SetRenderDrawColor(e->img, r, g, b, 255);
	SDL_RenderDrawPoint(e->img, x, y);
}
