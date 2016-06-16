#include "mysdl.h"
#include <unistd.h>

int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti);
void	init_scene(t_scene *scene, int width, int height);

int		sdl_main_loop(t_env *e)
{
	int		opti;
	int		w;
	int		h;

	e->opti = 0;
	e->opti |= DIFFUSE;
	e->opti |= UNDERSAMPLE;
	e->opti |= SCREENSIZE;

	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);

	while (1)
	{
		if (sdl_events(e))
			return (0);
		if (e->opti & SCREENSIZE)
		{
			SDL_GetWindowSize(e->sc, &w, &h);
			buffer_reload(&e->buff, w, h, e->buff.aa);
			change_scenewh(e, w, h);
			e->opti ^= SCREENSIZE;
			printf("lol\n");
		}
		opti = e->opti;
		mainrt(e, &e->scene, &e->buff, opti);
		SDL_RenderPresent(e->img);
		usleep(100);
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
