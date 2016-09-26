/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:35:46 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:23:17 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void		init_dotlight(t_dotlight *light, t_vec3d pos, t_color color)
{
	light->pos = pos;
	light->color = color;
}

inline void	lambert(t_color *cl, t_dotlight *light, t_hit *hit, t_ray *ray)
{
	t_flt	lambert;

	lambert = vec_dotproduct(&ray->dir, &hit->normal);
	cl->r = MIN(1.0f, cl->r + lambert * light->color.r * hit->mtl->color.r);
	cl->g = MIN(1.0f, cl->g + lambert * light->color.g * hit->mtl->color.g);
	cl->b = MIN(1.0f, cl->b + lambert * light->color.b * hit->mtl->color.b);
}

inline void	phong(t_color *cl, t_dotlight *light, t_hit *hit, t_ray *ray)
{
	t_vec3d	phongdir;
	t_flt	phongterm;

	phongdir = vec_reflect(&ray->dir, &hit->normal);
	phongterm = MAX(vec_dotproduct(&phongdir, &hit->dir), 0.0f);
	phongterm = 1.f * powf(phongterm, 60.f);
	cl->r = MIN(1.f, cl->r + phongterm * light->color.r * hit->mtl->specular.r);
	cl->g = MIN(1.f, cl->g + phongterm * light->color.g * hit->mtl->specular.g);
	cl->b = MIN(1.f, cl->b + phongterm * light->color.b * hit->mtl->specular.b);
}

void		dotlight(t_color *cl, t_dotlight *light, t_hit *hit, t_scene *sc)
{
	t_hit	hitshadow;
	t_ray	ray;
	t_vec3d	dist;

	hitshadow.didit = 0;
	ray.pos = hit->hitpoint;
	dist = vec_sub(&light->pos, &hit->hitpoint);
	if (vec_dotproduct(&hit->normal, &dist) <= 0.0f)
		return ;
	hitshadow.t = sqrtf(vec_dotproduct(&dist, &dist));
	if (hitshadow.t <= 0.f)
		return ;
	ray.dir = vec_scale(&dist, (1.0f / hitshadow.t));
	if (sc->opti & SHADOW)
		ray_trace(&ray, sc->obj, &hitshadow);
	if (!hitshadow.didit)
	{
		if (sc->opti & DIFFUSE)
			lambert(cl, light, hit, &ray);
		if (sc->opti & SPECULAR)
			phong(cl, light, hit, &ray);
	}
}
