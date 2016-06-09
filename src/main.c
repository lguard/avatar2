#include "mysdl.h"
#include <unistd.h>
int		sdl_main_loop(t_env *e)
{
	while (1)
	{
		usleep(100);
		if (sdl_events(e))
			return (0);
		SDL_RenderPresent(e->img);
	}
}

int		sdl_init(t_env *e)
{
	SDL_Init(SDL_INIT_VIDEO);
	e->sc = SDL_CreateWindow("wold3d",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	640, 480, SDL_WINDOW_RESIZABLE);
	e->img = SDL_CreateRenderer(e->sc, 1, SDL_RENDERER_ACCELERATED);
	return (0);
}

void	sdl_quit(t_env *e)
{
	SDL_DestroyWindow(e->sc);
	SDL_Quit();
}
