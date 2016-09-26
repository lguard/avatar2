/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysdl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:09:53 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:45:57 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSDL_H
# define MYSDL_H

# define _BSD_SOURCE

# define UC unsigned char

# include <pthread.h>
# include <SDL.h>
# include <math.h>
# include "vec.h"
# include "rt.h"
# include "scene.h"
# include "buffer.h"
# include "raytrace.h"

typedef struct		s_env
{
	SDL_Window		*sc;
	SDL_Event		event;
	SDL_Renderer	*img;
	SDL_Surface		*surface;
	t_scene			scene;
	t_buffer		buff;
	char			cmd[255];
	int				cmd_cursor;
	int				opti;
	int				key;
	int				rotkey;
	int				toraytrace;
	int				lol;
	pthread_mutex_t	mutex_lock;
}					t_env;

/*
**	sdl_render.c
*/
void				sdl_putpxl(t_env *e, int x, int y, t_color cl);

/*
**	sdl_events.c
*/
int					sdl_events(t_env *env);
int					sdl_key_down(t_env *env);
int					sdl_key_up(t_env *env);
int					sdl_key_up2(t_env *env);
int					sdl_win_ev(t_env *env);
int					sdl_main_loop(t_env *e);
int					sdl_init(t_env *e, int width, int height);
void				sdl_quit(t_env *e);

/*
**	sdl_change_sample.c
*/
void				new_file(t_env *e);
void				change_scenewh(t_env *e, int width, int height);
void				change_sample(t_env *e);

/*
**	sdl_change_sample.c
*/
int					sdl_bukakke(t_env *e);
void				sdl_quit(t_env *e);
int					sdl_init(t_env *e, int width, int height);
int					sdl_main_loop(t_env *e);

/*
**	main.c
*/
void				change_screen_check(t_env *e);
double				timer(int set);
void				print_timer(t_scene *sc);

#endif
