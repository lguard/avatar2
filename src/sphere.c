#include "sphere.h"

void		hit_sphere(t_ray *ray, void *sphere, t_hit *hit)
{
	double		t0;
	double		t1;
	double		b;
	double		d;
	t_vec3d		r;
	t_sphere	*s;

	s = (t_sphere*)sphere;
	r = vec_sub(&s->pos, &ray->pos);
	b = vec_dotproduct(&ray->dir, &r);
	d = b*b - vec_dotproduct(&r, &r) + s->radius * s->radius;
	if (d < 0.0f)
		return ;
	t0 = b - sqrtf(d); 
	t1 = b + sqrtf(d);
	if (t0 > 0.1f && t0 < t1 && t0 < hit->t) {
		hit->t = t0;
	}
	else if (t1 > 0.1f && t1 < hit->t) {
		hit->t = t1;
	}
	else {
		return ;
	}
	hit->didit = 1;
	hit->mtl = &s->mtl;
	hit->dir = ray->dir;
	hit->normal = hit_normal(ray, s, hit);
	return ;
}
// todo: metre toute les fonction de normal dans des list pour eviter de les calculer 2 fois
t_vec3d		hit_normal(t_ray *ray, t_sphere *s, t_hit *hit)
{
	hit->hitpoint = vec_scale(&ray->dir, hit->t);
	hit->hitpoint = vec_add(&hit->hitpoint, &ray->pos);
	t_vec3d		normal = vec_sub(&hit->hitpoint, &s->pos);
	vec_normalize(&normal);
	return normal;
}
