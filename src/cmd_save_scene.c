/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_save_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:35:41 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:44:04 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	value_to_file(int fd, void *v, int16_t size, int16_t type)
{
	write(fd, &type, (sizeof(int16_t)));
	write(fd, v, size);
}

void	write_s(const char *pathname, t_scene *e)
{
	int		fd;
	t_list	*ptr;

	fd = open(pathname, O_CREAT | O_WRONLY, S_IROTH | S_IRWXU);
	if (fd < 0)
		return ;
	ptr = e->light;
	while (ptr)
	{
		value_to_file(fd, (void*)(ptr->data), sizeof(t_dotlight), 0);
		ptr = ptr->next;
	}
	ptr = e->obj;
	while (ptr)
	{
		if (((t_obj*)(ptr->data))->type == 5)
			value_to_file(fd, ((t_obj*)ptr->data)->object, sizeof(t_plane),
			((t_obj*)(ptr->data))->type);
		else
			value_to_file(fd, ((t_obj*)ptr->data)->object, sizeof(t_quad),
			((t_obj*)(ptr->data))->type);
		ptr = ptr->next;
	}
	value_to_file(fd, &e->cam, sizeof(t_cam), 6);
}

void	save_to_file(t_env *e, char **cmd)
{
	if (cmd[1])
	{
		write_s(cmd[1], &e->scene);
		print("save to: %s\n", cmd[1]);
	}
}
