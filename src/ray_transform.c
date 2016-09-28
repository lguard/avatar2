/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:47 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:24:32 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ray_translate(t_ray *ray, t_flt tx, t_flt ty, t_flt tz)
{
	ray->pos.x += tx;
	ray->pos.y += ty;
	ray->pos.z += tz;
}

void	ray_rotate(t_ray *ray, t_flt rx, t_flt ry, t_flt rz)
{
	ray->pos = vec_rotaion_z(&ray->pos, rz);
	ray->pos = vec_rotaion_y(&ray->pos, ry);
	ray->pos = vec_rotaion_x(&ray->pos, rx);
	ray->dir = vec_rotaion_z(&ray->dir, rz);
	ray->dir = vec_rotaion_y(&ray->dir, ry);
	ray->dir = vec_rotaion_x(&ray->dir, rx);
}

void	ray_scale(t_ray *ray, t_flt tx, t_flt ty, t_flt tz)
{
	ray->pos.x *= tx;
	ray->pos.y *= ty;
	ray->pos.z *= tz;
	ray->dir.x *= tx;
	ray->dir.y *= ty;
	ray->dir.z *= tz;
	vec_normalize(&ray->dir);
}

/*
**	ray_scale(&ray, 1.f / ms->x, 1.f / ms->y, 1.f / ms->z);
*/

t_ray	ray_invertmat(t_ray *srcray, t_vec3d *mt, t_vec3d *mr, t_vec3d *ms)
{
	t_ray	ray;

	ray = *srcray;
	ray_translate(&ray, -mt->x, -mt->y, -mt->z);
	ray_rotate(&ray, -mr->x, -mr->y, -mr->z);
	(void)ms;
	return (ray);
}
