#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "mysdl.h"
#include "light.h"
#include "cmd.h"
#include "libft.h"
#include "raytrace.h"

void	change_screen_check(t_env *e)
{
	int	width;
	int	height;

	SDL_GetWindowSize(e->sc, &width, &height);
	if ((width == e->scene.render_width) &&
	(height == e->scene.render_height))
		return ;
	buffer_reload(&e->buff, width, height, e->buff.aa);
	change_scenewh(e, width, height);
	e->toraytrace = 1;
}

int		sdl_bukake(t_env *e)
{
	if (sdl_events(e))
	{
		e->lol = 1;
		return (1) ;
	}
	if (e->opti & SCREENSIZE)
	{
		change_screen_check(e);
		e->opti ^= SCREENSIZE;
	}
	if (e->key || e->rotkey)
		e->toraytrace = 1;
	if (e->key != 0)
		handle_move(&e->scene.cam, e->key, 200);
	if (e->rotkey != 0)
		handle_rot(&e->scene.cam, e->rotkey, 0.2);
	e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
	return (0);
}

double	timer(int set)
{
	struct timeval	time;
	static double	sec1;
	long			cur_time;

	if(gettimeofday(&time, 0))
		return (0);
	if (set)
	{
		cur_time = 1000000 * time.tv_sec + time.tv_usec;
		sec1 = cur_time / 1000000.0;
	}
	else
	{
		cur_time = 1000000 * time.tv_sec + time.tv_usec;
		return ((double)(cur_time / 1000000.0) - sec1);
	}
	return (0);
}

int		sdl_main_loop(t_env *e)
{
	int		w;
	int		h;

	SDL_GetWindowSize(e->sc, &w, &h);
	buffer_reload(&e->buff, w, h, e->buff.aa);
	change_scenewh(e, w, h);
	while (!e->lol)
	{
		pthread_mutex_lock(&e->mutex_lock);
		if (sdl_bukake(e))
		{
			pthread_mutex_unlock(&e->mutex_lock);
			break ;
		}
		if (e->toraytrace)
		{
			e->toraytrace = 0;
			e->scene.opti = e->opti;
			timer(1);
			mainrt(e, &e->scene, &e->buff);
			print("%f\n", timer(0));
		}
		SDL_RenderPresent(e->img);
		pthread_mutex_unlock(&e->mutex_lock);
	}
	return (0);
}

int		sdl_init(t_env *e, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	e->sc = SDL_CreateWindow("avatar2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	width, height, SDL_WINDOW_RESIZABLE);
	e->img = SDL_CreateRenderer(e->sc, 1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);
	e->key = 0;
	e->rotkey = 0;
	e->toraytrace = 1;
	e->lol = 0;
	e->scene.obj = NULL;
	e->scene.light = NULL;
	e->scene.reflect = 2;
	e->scene.progressbar = 0;
	e->opti = 0;
	e->opti |= DIFFUSE;
	e->opti |= UNDERSAMPLE;
	e->opti |= SCREENSIZE;
	pthread_mutex_init(&e->mutex_lock, NULL);
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

int	main(int ac, char **av)
{
	t_env		e;
	pthread_t	p;

	init(&e, &e.scene, &e.buff, 400, 500);
	if (ac > 1)
		load_from_file(&e, av);
	pthread_create(&p, NULL, parse_cmd, &e);
	sdl_main_loop(&e);
	sdl_quit(&e);
	pthread_join(p, NULL);
	list_delall(&e.scene.obj, &delete_object);
	list_delall(&e.scene.light, &light_free);
	buffer_free(&e.buff);
	return (0);
}
