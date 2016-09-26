/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:35:51 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:35:52 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void		addolight(t_list **lightlist, t_dotlight *light)
{
	light->id = get_id();
	list_pushfront(lightlist, (void*)light);
}

void		light_free(void *obj)
{
	free(obj);
}

t_dotlight	*getlight_by_id(int id, t_list *lightlist)
{
	while (lightlist)
	{
		if (((t_dotlight*)(lightlist->data))->id == id)
			return (lightlist->data);
		lightlist = lightlist->next;
	}
	return (NULL);
}

int			remove_light(void *obj, void *id)
{
	return (((t_dotlight*)obj)->id - *(uint16_t*)id);
}

t_dotlight	*light_default_dotlight(t_vec3d *pos)
{
	t_dotlight	*light;

	light = (t_dotlight*)malloc(sizeof(t_dotlight));
	vec_init(&light->pos, pos->x, pos->y, pos->z);
	color_init(&light->color, 1.0f, 1.0f, 1.0f);
	return (light);
}
