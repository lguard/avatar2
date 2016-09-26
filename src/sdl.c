/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:39:59 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:55:14 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl.h"

int		sdl_main_loop(t_env *e)
{
	new_file(e);
	while (!e->lol)
	{
		pthread_mutex_lock(&e->mutex_lock);
		SDL_RenderPresent(e->img);
		if (sdl_bukakke(e))
		{
			pthread_mutex_unlock(&e->mutex_lock);
			break ;
		}
		if (e->toraytrace)
		{
			e->toraytrace = 0;
			e->scene.opti = e->opti;
			mainrt(e, &e->scene, &e->buff);
		}
		else
		{
			pthread_mutex_unlock(&e->mutex_lock);
			usleep(1000);
			continue ;
		}
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

void	sdl_quit(t_env *e)
{
	SDL_DestroyWindow(e->sc);
	SDL_Quit();
}

int		sdl_bukakke(t_env *e)
{
	if (sdl_events(e))
	{
		e->lol = 1;
		return (1);
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
	e->scene.cam.viewplane_upleft =
	getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
	return (0);
}
