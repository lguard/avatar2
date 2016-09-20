#include "mysdl.h"
#include <string.h>

void	single_rt(t_scene *scene, int x, int y);

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
	if (env->event.key.keysym.sym == SDLK_UP)
		env->key |= UP;
	else if (env->event.key.keysym.sym == SDLK_DOWN)
		env->key |= DOWN;
	else if (env->event.key.keysym.sym == SDLK_LEFT)
		env->key |= LEFT;
	else if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->key |= RIGHT;
	else if (env->event.key.keysym.sym == SDLK_a)
		env->rotkey |= ROTPY;
	else if (env->event.key.keysym.sym == SDLK_w)
		env->rotkey |= ROTPX;
	else if (env->event.key.keysym.sym == SDLK_s)
		env->rotkey |= ROTPXB;
	else if (env->event.key.keysym.sym == SDLK_d)
		env->rotkey |= ROTPYB;
	else
		return (0);
	env->toraytrace = 1;
	return (0);
}

void	change_sample(t_env *e)
{
	e->scene.width = e->scene.render_width * e->buff.aa;
	e->scene.height = e->scene.render_height * e->buff.aa;
	if (e->opti & UNDERSAMPLE)
	{
		e->scene.width = e->scene.render_width / 2;
		e->scene.height = e->scene.render_height / 2;
	}
}

void	change_scenewh(t_env *e, int width, int height)
{
	e->scene.render_width = width;
	e->scene.render_height = height;
	change_sample(e);
	e->scene.cam.wfov = 1.0;
	e->scene.cam.hfov = 1.0 / ((float)width / (float)height);
	e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov,
	e->scene.cam.hfov);
}

int		sdl_key_up(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (env->event.key.keysym.sym == SDLK_UP)
		env->key ^= UP;
	else if (env->event.key.keysym.sym == SDLK_DOWN)
		env->key ^= DOWN;
	else if (env->event.key.keysym.sym == SDLK_LEFT)
		env->key ^= LEFT;
	else if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->key ^= RIGHT;
	else if (env->event.key.keysym.sym == SDLK_a)
		env->rotkey ^= ROTPY;
	else if (env->event.key.keysym.sym == SDLK_w)
		env->rotkey ^= ROTPX;
	else if (env->event.key.keysym.sym == SDLK_s)
		env->rotkey ^= ROTPXB;
	else if (env->event.key.keysym.sym == SDLK_d)
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
	else if (env->event.key.keysym.sym == SDLK_4)
		env->opti ^= REFRACTION;
	else if (env->event.key.keysym.sym == SDLK_5)
	{
		env->opti ^= UNDERSAMPLE;
		change_sample(env);
	}
	return (0);
}

int		sdl_mouse_down(t_env *env)
{
	single_rt(&env->scene, env->event.button.x, env->event.button.y);
	return (0);
}

int		sdl_win_ev(t_env *e)
{
	e->opti |= SCREENSIZE;
	e->toraytrace = 1;
	return (0);
}
