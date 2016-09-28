/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:05 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:52:21 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "mysdl.h"
#include "light.h"
#include "cmd.h"
#include "libft.h"

void	change_screen_check(t_env *e)
{
	int	width;
	int	height;

	SDL_GetWindowSize(e->sc, &width, &height);
	if ((width == e->scene.render_width) &&
	(height == e->scene.render_height))
		return ;
	buffer_reload(&e->buff, width, height, e->buff.aa);
	change_scenewh(e, width, height);
	e->toraytrace = 1;
}

double	timer(int set)
{
	struct timeval	time;
	static double	sec1;
	long			cur_time;

	if (gettimeofday(&time, 0))
		return (0);
	if (set)
	{
		cur_time = 1000000 * time.tv_sec + time.tv_usec;
		sec1 = cur_time / 1000000.0;
	}
	else
	{
		cur_time = 1000000 * time.tv_sec + time.tv_usec;
		return ((double)(cur_time / 1000000.0) - sec1);
	}
	return (0);
}

void	print_timer(t_scene *sc)
{
	if (sc->progressbar)
	{
		sc->progressbar = 0;
		print("\ndone in %f sec\n\x1b[32mavatar2->\x1b[0m", timer(0));
	}
}

void	init(t_env *e, t_scene *sc, int width, int height)
{
	sdl_init(e, width, height);
	init_scene(sc, width, height);
	buffer_init(&e->buff);
}

int		main(int ac, char **av)
{
	t_env		e;
	pthread_t	p;

	init(&e, &e.scene, 500, 400);
	if (ac > 1)
		load_from_file(&e, av);
	pthread_create(&p, NULL, parse_cmd, &e);
	sdl_main_loop(&e);
	sdl_quit(&e);
	pthread_join(p, NULL);
	list_delall(&e.scene.obj, &delete_object);
	list_delall(&e.scene.light, &light_free);
	buffer_free(&e.buff);
	return (0);
}
