/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_delet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:09:07 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:09:30 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	delete_object(void *obj)
{
	t_obj	*object;

	object = (t_obj*)obj;
	free(object->object);
	free(obj);
}

int		remove_obj(void *obj, void *id)
{
	return (((t_id*)obj)->id - *(uint16_t*)id);
}
