#include "mysdl.h"
#include <string.h>

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
	if (env->event.key.keysym.sym == SDLK_UP)
		env->rotkey |= ROTPX;
	else if (env->event.key.keysym.sym == SDLK_DOWN)
		env->rotkey |= ROTPXB;
	else if (env->event.key.keysym.sym == SDLK_LEFT)
		env->rotkey |= ROTPY;
	else if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->rotkey |= ROTPYB;
	else if (env->event.key.keysym.sym == SDLK_a)
		env->key |= LEFT;
	else if (env->event.key.keysym.sym == SDLK_w)
		env->key |= UP;
	else if (env->event.key.keysym.sym == SDLK_s)
		env->key |= DOWN;
	else if (env->event.key.keysym.sym == SDLK_d)
		env->key |= RIGHT;
	else
		return (0);
	env->toraytrace = 1;
	return (0);
}

int		sdl_key_up(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (env->event.key.keysym.sym == SDLK_w)
		env->key ^= UP;
	else if (env->event.key.keysym.sym == SDLK_s)
		env->key ^= DOWN;
	else if (env->event.key.keysym.sym == SDLK_a)
		env->key ^= LEFT;
	else if (env->event.key.keysym.sym == SDLK_d)
		env->key ^= RIGHT;
	else if (env->event.key.keysym.sym == SDLK_UP)
		env->rotkey ^= ROTPX;
	else if (env->event.key.keysym.sym == SDLK_DOWN)
		env->rotkey ^= ROTPXB;
	else if (env->event.key.keysym.sym == SDLK_LEFT)
		env->rotkey ^= ROTPY;
	else if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->rotkey ^= ROTPYB;
	else
		return (sdl_key_up2(env));
	env->toraytrace = 0;
	return (0);
}

int		sdl_key_up2(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_0)
		env->opti ^= DIFFUSE;
	else if (env->event.key.keysym.sym == SDLK_1)
		env->opti ^= SHADOW;
	else if (env->event.key.keysym.sym == SDLK_2)
		env->opti ^= SPECULAR;
	else if (env->event.key.keysym.sym == SDLK_3)
		env->opti ^= REFLECTION;
	else if (env->event.key.keysym.sym == SDLK_5)
		env->opti ^= REFRACTION;
	else if (env->event.key.keysym.sym == SDLK_4)
	{
		env->opti ^= UNDERSAMPLE;
		change_sample(env);
	}
	return (0);
}

int		sdl_win_ev(t_env *e)
{
	e->opti |= SCREENSIZE;
	return (0);
}
