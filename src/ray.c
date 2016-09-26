/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:43 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:06:42 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "ray.h"

void		ray_trace(t_ray *ray, t_list *obj, t_hit *hit)
{
	while (obj)
	{
		(void)hit;
		(void)ray;
		((t_obj*)(obj->data))->hit(ray, ((t_obj*)(obj->data))->object, hit);
		obj = obj->next;
	}
}

inline void	hit_switch(t_flt *t, int id, t_hit *hit, t_ray *ray)
{
	if (t[0] > 0.1f && t[0] < t[1] && t[0] < hit->t)
	{
		hit->t = t[0];
	}
	else if (t[1] > 0.1f && t[1] < hit->t)
	{
		hit->t = t[1];
	}
	else
	{
		return ;
	}
	hit->id = id;
	hit->didit = 1;
	hit->dir = ray->dir;
	hit->raypos = ray->pos;
}

inline void	hit_clear(t_hit *hit)
{
	hit->didit = 0;
	hit->t = 2000000;
}

uint16_t	get_id(void)
{
	static uint16_t i = 0;

	return (i++);
}
