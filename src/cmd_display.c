/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:33:57 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:34:10 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

char	*type_to_char(uint16_t type)
{
	if (type == 1)
		return ("sphe");
	if (type == 2)
		return ("cone");
	if (type == 3)
		return ("cyli");
	if (type == 4)
		return ("hype");
	if (type == 5)
		return ("plan");
	else
		return ("");
}

void	display_light(t_scene *sc)
{
	t_list		*ptr;
	t_dotlight	*dl;

	ptr = sc->light;
	while (ptr)
	{
		dl = (t_dotlight*)ptr->data;
		print("id:%u, pos:x%f,y%fz,%f color:\x1b[31mr%f,\
\x1b[32mg%f,\x1b[34mb%f\x1b[0m\n",
		dl->id, dl->pos.x, dl->pos.y, dl->pos.z, dl->color.g, dl->color.r,
		dl->color.b);
		ptr = ptr->next;
	}
}

void	display_object(t_scene *sc)
{
	t_list			*ptr;
	t_obj			*obj;
	t_obj_header	*head;

	ptr = sc->obj;
	while (ptr)
	{
		obj = (t_obj*)ptr->data;
		head = obj->object;
		print("id:%u, type:%s, pos x:%f y:%f z:%f, ",
		obj->id, type_to_char(obj->type),
		head->matt.x, head->matt.y, head->matt.z);
		print("matr: x:%f y:%f z:%f\n",
		head->matr.x, head->matr.y, head->matr.z);
		ptr = ptr->next;
	}
}

void	display_scene(t_env *env)
{
	display_light(&env->scene);
	display_object(&env->scene);
}
