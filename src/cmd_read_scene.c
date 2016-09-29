/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_read_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:35:37 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:43:27 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		select_surface(int fd, t_scene *scene, uint16_t type)
{
	if (type == 0)
		load_light(fd, scene);
	else if (type == 1)
		load_sphere(fd, scene);
	else if (type == 2)
		load_cone(fd, scene);
	else if (type == 3)
		load_cylindre(fd, scene);
	else if (type == 4)
		load_hyperbol(fd, scene);
	else if (type == 5)
		load_plane(fd, scene);
	else if (type == 6)
		load_cam(fd, scene);
	else
		return (1);
	return (0);
}

void	read_scene(const char *pathname, t_scene *scene)
{
	int		fd;
	int16_t	type;

	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		return ;
	list_delall(&scene->obj, &delete_object);
	list_delall(&scene->light, &light_free);
	while (42)
	{
		if (read(fd, &type, sizeof(int16_t)) <= 0)
			break ;
		if (select_surface(fd, scene, type))
			break ;
	}
	close(fd);
}

void	load_from_file(t_env *e, char **cmd)
{
	if (cmd[1])
	{
		read_scene(cmd[1], &e->scene);
		new_file(e);
		print("load : %s\n", cmd[1]);
	}
	e->toraytrace = 1;
	e->scene.progressbar = 1;
}
