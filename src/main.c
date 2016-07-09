#include "mysdl.h"
#include <unistd.h>
#include <sys/time.h>

int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti);
void	init_scene(t_scene *scene, int width, int height);
void	handle_move(t_cam *cam, int key, FLOAT frame);
void	handle_rot(t_cam *cam, int key, FLOAT frame);

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
		}
		if (e->key != 0 || e->rotkey !=0)
		{
			opti = e->opti;
			struct timeval time;
			if(gettimeofday( &time, 0 ))
				return -1;
			long cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec1 = cur_time / 1000000.0;
			mainrt(e, &e->scene, &e->buff, opti);
			SDL_RenderPresent(e->img);
			if(gettimeofday( &time, 0 ))
				return -1;
			cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec2 = cur_time / 1000000.0;
			/*printf("%f\n", sec2-sec1);*/
			if (e->key != 0) {
				handle_move(&e->scene.cam, e->key, sec2-sec1);
			}
			if (e->rotkey != 0) {
				handle_rot(&e->scene.cam, e->rotkey, sec2-sec1);
			}
			e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
		}
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
	e->key = 0;
	e->rotkey = 0;
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

	init(&e, &e.scene, &e.buff, 400, 500);
	sdl_main_loop(&e);
	return 0;
}
