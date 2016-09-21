#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "mysdl.h"
#include "light.h"
#include "cmd.h"
#include "libft.h"


int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti);
void	init_scene(t_scene *scene, int width, int height);
void	handle_move(t_cam *cam, int key, FLOAT frame);
void	handle_rot(t_cam *cam, int key, FLOAT frame);

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

int		sdl_main_loop(t_env *e)
{
	int		opti;
	int		w;
	int		h;

	e->opti = 0;
	e->opti |= DIFFUSE;
	e->opti |= UNDERSAMPLE;
	e->opti |= SCREENSIZE;

	SDL_StopTextInput();
	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);

	SDL_GetWindowSize(e->sc, &w, &h);
	buffer_reload(&e->buff, w, h, e->buff.aa);
	change_scenewh(e, w, h);
	while (!e->lol)
	{
		pthread_mutex_lock(&e->mutex_lock);
		if (sdl_events(e))
		{
			e->lol = 1;
			pthread_mutex_unlock(&e->mutex_lock);
			break ;
		}
		if (e->opti & SCREENSIZE)
		{
			change_screen_check(e);
			e->opti ^= SCREENSIZE;
		}
		if (e->key || e->rotkey)
			e->toraytrace = 1;
		if (e->toraytrace)
		{
			e->toraytrace = 0;
			opti = e->opti;
			struct timeval time;
			if(gettimeofday( &time, 0 ))
				return -1;
			long cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec1 = cur_time / 1000000.0;
			mainrt(e, &e->scene, &e->buff, opti);
			if(gettimeofday( &time, 0 ))
				return -1;
			cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec2 = cur_time / 1000000.0;
			if (e->key != 0)
				handle_move(&e->scene.cam, e->key, (sec2-sec1)*240);
			if (e->rotkey != 0)
				handle_rot(&e->scene.cam, e->rotkey, (sec2-sec1)*4);
			e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
		}
		SDL_RenderPresent(e->img);
		pthread_mutex_unlock(&e->mutex_lock);
	}
	sdl_quit(e);
	return (0);
}

int		sdl_init(t_env *e, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	e->sc = SDL_CreateWindow("avatar2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	width, height, SDL_WINDOW_RESIZABLE);
	e->img = SDL_CreateRenderer(e->sc, 1, SDL_RENDERER_ACCELERATED);
	e->key = 0;
	e->rotkey = 0;
	e->toraytrace = 1;
	e->lol = 0;
	e->scene.obj = NULL;
	e->scene.light = NULL;
	e->scene.reflect = 2;
	e->scene.progressbar = 0;
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

int	main(void)
{
	t_env		e;
	pthread_t	p;

	init(&e, &e.scene, &e.buff, 400, 500);
	pthread_create(&p, NULL, parse_cmd, &e);
	sdl_main_loop(&e);
	pthread_join(p, NULL);
	list_delall(&e.scene.obj, &delete_object);
	list_delall(&e.scene.light, &light_free);
	buffer_free(&e.buff);
	return (0);
}
