#include "mysdl.h"
#include <unistd.h>

int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti);
void	init_scene(t_scene *scene, int width, int height);

int		sdl_main_loop(t_env *e)
{
	int		opti;

	e->opti = 0;
	e->opti |= DIFFUSE;
	e->opti |= UNDERSAMPLE;

	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);

	while (1)
	{
		usleep(100);
		if (sdl_events(e))
			return (0);
		opti = e->opti;
		mainrt(e, &e->scene, &e->buff, opti);
		SDL_RenderPresent(e->img);
	}
	sdl_quit(e);
}

int		sdl_init(t_env *e, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	e->sc = SDL_CreateWindow("avatar2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	width, height, SDL_WINDOW_RESIZABLE);
	e->img = SDL_CreateRenderer(e->sc, 1, SDL_RENDERER_ACCELERATED);
	return (0);
}

void	init(t_env *e, t_scene *sc, t_buffer *buff, int width, int height)
{
	sdl_init(e, width, height);
	init_scene(sc, width, height);
	buffer_init(buff);
	buffer_reload(buff, width, height, 1);
}

void	sdl_quit(t_env *e)
{
	SDL_DestroyWindow(e->sc);
	SDL_Quit();
}

int main(void)
{
	t_env		e;

	init(&e, &e.scene, &e.buff, 1000, 1000);
	sdl_main_loop(&e);
	return 0;
}
