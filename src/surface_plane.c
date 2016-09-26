/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:37:53 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:00:03 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

void		hit_plane(t_ray *ray, void *plane, t_hit *hit)
{
	t_plane	*p;
	t_flt	t;
	t_flt	j;
	t_vec3d	a;

	p = (t_plane*)plane;
	j = vec_dotproduct(&p->normal, &ray->dir);
	if (j == 0.f)
		return ;
	a = vec_sub(&p->pos, &ray->pos);
	t = vec_dotproduct(&p->normal, &a);
	t /= j;
	if (t < 0.1f || t > hit->t)
		return ;
	hit->t = t;
	hit->didit = 1;
	hit->mtl = &p->mtl;
	hit->dir = ray->dir;
	hit->reflect = p->mtl.reflect;
	hit->normal = p->normal;
	hit->hitpoint = vec_scale(&ray->dir, hit->t);
	hit->hitpoint = vec_add(&hit->hitpoint, &ray->pos);
	hit->id = p->id;
}

void		surface_plane(t_ray *srcray, void *plane, t_hit *hit)
{
	t_plane	*p;
	t_flt	t[2];
	t_flt	j;
	t_ray	ray;

	t[1] = 200000000;
	p = (t_plane*)plane;
	ray = ray_invertmat(srcray, &p->matt, &p->matr, &p->mats);
	j = ray.dir.y;
	if (j == 0.f)
		return ;
	t[0] = 0 - ray.pos.y;
	t[0] /= j;
	hit_switch(t, p->id, hit, &ray);
}

void		surface_plane_normal(void *plane, t_hit *hit)
{
	(void)plane;
	vec_init(&hit->normal, 0, 1.f, 0);
}

t_plane		*surface_default_plane(t_vec3d *pos)
{
	t_plane *sphere;

	sphere = (t_plane*)malloc(sizeof(t_plane));
	vec_init(&sphere->matt, pos->x, pos->y, pos->z);
	vec_init(&sphere->matr, 0, 0, 0);
	vec_init(&sphere->mats, 1, 1, 1);
	vec_init(&sphere->normal, 0, 1, 0);
	color_init(&sphere->mtl.color, 1.0f, 1.0f, 0.0f);
	color_init(&sphere->mtl.specular, 1.0f, 1.0f, 1.0f);
	sphere->mtl.reflect = 0.1;
	return (sphere);
}
