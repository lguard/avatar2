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

void change_sample(t_env *e)
{
	e->scene.width = e->scene.render_width * e->buff.aa;
	e->scene.height = e->scene.render_height * e->buff.aa;
	if (e->opti & UNDERSAMPLE)
	{
		e->scene.width = e->scene.render_width / 2;
		e->scene.height = e->scene.render_height / 2;
	}
}

void	change_scenewh(t_env *e)
{
	e->scene.render_width = width;
	e->scene.render_height = height;
	e->scene.width = scene->render_width * 1;
	e->scene.height = scene->render_height * 1;
	e->scene.cam.wfov = 1.0;
	e->scene.cam.hfov = 1.0 / ((float)width / (float)height);
	e->scene.cam.rightvec = vec_mul(&scene->cam.dirvec, &scene->cam.upvec);
	e->scene.cam.viewplane_upleft = getupleft(&scene->cam, scene->cam.wfov, scene->cam.hfov);
	e->scene.cam.distance = 1.f;
}

int		sdl_key_up(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		return (1);

	if (env->event.key.keysym.sym == SDLK_1)
		env->opti ^= SPECULAR;
	if (env->event.key.keysym.sym == SDLK_2)
		env->opti ^= DIFFUSE;
	if (env->event.key.keysym.sym == SDLK_3)
		env->opti ^= REFLECTION;
	if (env->event.key.keysym.sym == SDLK_4)
		env->opti ^= REFRACTION;
	if (env->event.key.keysym.sym == SDLK_5)
	{
	// changer lesvariable en fin de calcule
		env->opti ^= UNDERSAMPLE;
		change_scenewh(env);
	}
	return (0);
}


int		sdl_mouse_down(t_env *env)
{
	/*single_rt(env->event.button.x , env->event.button.y);*/
	(void)env;
	return (0);
}

int		sdl_win_ev(t_env *e)
{
	(void)e;
	// changer lesvariable en fin de calcule
	/*int		w;*/
	/*int 	h;*/

	/*SDL_GetWindowSize(e->sc, &w, &h);*/
	/*change_scenewh(e);*/
	/*buffer_reload(&e->buff, w, h, e->buff.aa);*/
	return (0);
}
