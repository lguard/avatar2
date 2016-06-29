#ifndef MYSDL_H
# define MYSDL_H

#define _BSD_SOURCE

# include <SDL.h>
# include <math.h>
# include "vec.h"
# include "rt.h"
# include "scene.h"
# include "buffer.h"

typedef struct		s_env
{
	SDL_Window		*sc;
	SDL_Event		event;
	SDL_Renderer	*img;
	SDL_Surface		*surface;
	t_scene			scene;
	t_buffer		buff;
	int				opti;
	int				key;
}					t_env;

void	sdl_putpxl(t_env *e, int x, int y, unsigned char r, unsigned char g, unsigned char b);

int		sdl_events(t_env *env);
int		sdl_key_down(t_env *env);
int		sdl_key_up(t_env *env);
int		sdl_mouse_down(t_env *env);
int		sdl_win_ev(t_env *env);
int		sdl_main_loop(t_env *e);
int		sdl_init(t_env *e, int width, int height);
void	sdl_quit(t_env *e);
void	change_scenewh(t_env *e, int width, int height);
void	change_sample(t_env *e);

#endif /* MYSDL_H */
