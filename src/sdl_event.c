#include "mysdl.h"

int		sdl_events(t_env *env)
{
	while (SDL_PollEvent(&env->event))
	{
		if (env->event.type == SDL_KEYDOWN)
			sdl_key_down(env);
		if (env->event.type == SDL_KEYUP)
			return (sdl_key_up(env));
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

int		sdl_win_ev(t_env *env)
{
	(void)env;
	return (0);
}
