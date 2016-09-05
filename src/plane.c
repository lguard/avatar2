#include "plane.h"

void		hit_plane(t_ray *ray, void *plane, t_hit *hit)
{
	t_plane	*p;
	FLOAT	t;
	FLOAT	j;
	p = (t_plane*)plane;
	t_vec3d	a;

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
	FLOAT	t;
	FLOAT	j;
	t_ray	ray;

	p = (t_plane*)plane;
	ray = ray_invertmat(srcray, &p->matt, &p->matr, &p->mats);

	j = ray.dir.y;
	if (j == 0.f)
		return ;
	t = 0 - ray.pos.y;
	t /= j;
	hit_switch(t, 20000000, p->id, hit, &ray);
}

void	surface_plane_normal(void *plane, t_hit *hit)
{
	(void)plane;
	vec_init(&hit->normal, 0, 1.f, 0);
}
