#include "quad.h"

void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hb;
	t_ray		ray;
	t_vec3d		param;
	FLOAT		t0 = 2000000;
	FLOAT		t1 = 2000000;

	hb = (t_quad*)quad;
	vec_init(&param, hb->a, hb->b, hb->c);
	ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);
	solve_quadraticv2(&t0, &t1, dot_produce_elips(ray.dir, ray.dir, param),
	2*dot_produce_elips(ray.dir, ray.pos, param) ,
	dot_produce_elips(ray.pos, ray.pos, param) + hb->r);
	hit_switch(t0, t1, hb->id, hit, &ray);
	return ;
}

void		surface_hyperboloid_normal(void *quad, t_hit *hit)
{
	t_quad	*hb;

	hb = (t_quad*)quad;
	hit->normal.x = 2*hit->hitpoint.x *hb->a;
	hit->normal.y = 2*hit->hitpoint.y *hb->b;
	hit->normal.z = 2*hit->hitpoint.z *hb->c;
	vec_normalize(&hit->normal);
}
