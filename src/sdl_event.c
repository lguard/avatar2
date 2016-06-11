#include "mysdl.h"

void	single_rt(int x, int y);

int		sdl_events(t_env *env)
{
	while (SDL_PollEvent(&env->event))
	{
		if (env->event.type == SDL_KEYDOWN)
			sdl_key_down(env);
		if (env->event.type == SDL_KEYUP)
			return (sdl_key_up(env));
		if (env->event.type == SDL_MOUSEBUTTONDOWN)
			sdl_mouse_down(env);
		if (env->event.type == SDL_WINDOWEVENT)
			sdl_win_ev(env);
	}
	return (0);
}

int		sdl_key_down(t_env *env)
{
	(void)env;
	return (0);
}

int		sdl_key_up(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	return (0);
}


int		sdl_mouse_down(t_env *env)
{
	/*single_rt(env->event.button.x , env->event.button.y);*/
	(void)env;
	return (0);
}

int		sdl_win_ev(t_env *env)
{
	(void)env;
	return (0);
}
