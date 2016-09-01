#include "quad.h"

void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hyperboloid;
	t_ray		ray;
	FLOAT		t0;
	FLOAT		t1;

	t_vec3d	test = {0.0002, -0.0002, 0.0002};
	hyperboloid = (t_quad*)quad;
	ray = ray_invertmat(srcray, &hyperboloid->matt, &hyperboloid->matr, &hyperboloid->mats);
	solve_quadraticv2(&t0, &t1, dot_produce_elips(ray.dir, ray.dir, test), 2*dot_produce_elips(ray.dir, ray.pos, test) ,dot_produce_elips(ray.pos, ray.pos, test)- 1);
	hit_switch(t0, t1, hyperboloid->id, hit);
	return ;
}

void		surface_hyperboloid_normal(void *quad, t_hit *hit)
{
	t_quad	*hyperboloid;

	hyperboloid = (t_quad*)quad;
	hit->normal.x = 2*hit->hitpoint.x *hyperboloid->param.x;
	hit->normal.y = 2*hit->hitpoint.y *hyperboloid->param.y;
	hit->normal.z = 2*hit->hitpoint.z *hyperboloid->param.z;
	vec_normalize(&hit->normal);
}
