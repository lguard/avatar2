/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_load_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:34:51 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:34:52 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void		load_light(int fd, t_scene *scene)
{
	t_dotlight	*light;

	light = (t_dotlight*)malloc(sizeof(t_dotlight));
	read(fd, light, sizeof(t_dotlight));
	addolight(&scene->light, light);
}

void		load_cam(int fd, t_scene *scene)
{
	read(fd, &scene->cam, sizeof(t_cam));
}
