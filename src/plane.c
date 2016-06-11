#include "plane.h"

void		hit_plane(t_ray *ray, void *plane, t_hit *hit)
{
	t_plane	*p;
	double	t;
	double	j;
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
