#include "mysdl.h"
#include <unistd.h>

int mainrt(t_env *e);

int		sdl_main_loop(t_env *e)
{
	sdl_init(e);
	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);

	mainrt(e);
	while (1)
	{
		usleep(100);
		if (sdl_events(e))
			return (0);
		SDL_RenderPresent(e->img);
	}
	sdl_quit(e);
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

int main(void)
{
	t_env	e;

	sdl_main_loop(&e);
	return 0;
}
