#include "mysdl.h"
#include <string.h>

void	single_rt(t_scene *scene, int x, int y);

void	sdl_input(t_env *env)
{
	int len;
	int len2;

	len = strlen(env->event.text.text);
	if ((len + env->cmd_cursor > 255))
		len = (len + env->cmd_cursor) - 255;
	len2 = strlen(env->cmd+env->cmd_cursor);
	memmove(env->cmd+env->cmd_cursor+len, env->cmd+env->cmd_cursor, len2);
	strncpy((env->cmd)+env->cmd_cursor, env->event.text.text, len);
	printf("%s\n", env->cmd);
	env->cmd_cursor += len;
}

void	cursor_left(t_env *env)
{
	if (env->cmd_cursor > 0)
		--env->cmd_cursor;
}

void	cursor_right(t_env *env)
{
	if (env->cmd_cursor < 254 && env->cmd[env->cmd_cursor] != '\0')
		++env->cmd_cursor;
}

void	cursor_supress(t_env *env)
{
	int	len;

	if (env->cmd_cursor == 0)
		return;
	len = strlen(env->cmd+env->cmd_cursor);
	memmove(env->cmd+env->cmd_cursor-1, env->cmd+env->cmd_cursor, len);
	env->cmd[env->cmd_cursor+len-1] = '\0';
	--env->cmd_cursor;
}

int		sdl_events(t_env *env)
{
	while (SDL_PollEvent(&env->event))
	{
		if (env->event.type == SDL_TEXTINPUT)
			sdl_input(env);
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
	if (SDL_IsTextInputActive())
	{
		if (env->event.key.keysym.sym == SDLK_LEFT)
			cursor_left(env);
		if (env->event.key.keysym.sym == SDLK_RIGHT)
			cursor_right(env);
		if (env->event.key.keysym.sym == SDLK_DELETE)
			cursor_supress(env);
		return (0);
	}
	if (env->event.key.keysym.sym == SDLK_UP)
		env->key |= UP;
	if (env->event.key.keysym.sym == SDLK_DOWN)
		env->key |= DOWN;
	if (env->event.key.keysym.sym == SDLK_LEFT)
		env->key |= LEFT;
	if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->key |= RIGHT;
	if (env->event.key.keysym.sym == SDLK_a)
		env->rotkey |= ROTPY;
	if (env->event.key.keysym.sym == SDLK_w)
		env->rotkey |= ROTPX;
	if (env->event.key.keysym.sym == SDLK_s)
		env->rotkey |= ROTPXB;
	if (env->event.key.keysym.sym == SDLK_d)
		env->rotkey |= ROTPYB;
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

void	change_scenewh(t_env *e, int width, int height)
{
	e->scene.render_width = width;
	e->scene.render_height = height;
	change_sample(e);
	e->scene.cam.wfov = 1.0;
	e->scene.cam.hfov = 1.0 / ((float)width / (float)height);
	e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
}

int		sdl_key_up(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	if (SDL_IsTextInputActive())
		return (0);
	if (env->event.key.keysym.sym == SDLK_0)
		env->opti ^= DIFFUSE;
	if (env->event.key.keysym.sym == SDLK_1)
		env->opti ^= SHADOW;
	if (env->event.key.keysym.sym == SDLK_2)
		env->opti ^= SPECULAR;
	if (env->event.key.keysym.sym == SDLK_3)
		env->opti ^= REFLECTION;
	if (env->event.key.keysym.sym == SDLK_4)
		env->opti ^= REFRACTION;
	if (env->event.key.keysym.sym == SDLK_5)
	{
		env->opti ^= UNDERSAMPLE;
		change_sample(env);
	}
	if (env->event.key.keysym.sym == SDLK_UP)
		env->key ^= UP;
	if (env->event.key.keysym.sym == SDLK_DOWN)
		env->key ^= DOWN;
	if (env->event.key.keysym.sym == SDLK_LEFT)
		env->key ^= LEFT;
	if (env->event.key.keysym.sym == SDLK_RIGHT)
		env->key ^= RIGHT;
	if (env->event.key.keysym.sym == SDLK_a)
		env->rotkey ^= ROTPY;
	if (env->event.key.keysym.sym == SDLK_w)
		env->rotkey ^= ROTPX;
	if (env->event.key.keysym.sym == SDLK_s)
		env->rotkey ^= ROTPXB;
	if (env->event.key.keysym.sym == SDLK_d)
		env->rotkey ^= ROTPYB;
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
	return (0);
}
