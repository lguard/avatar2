#include "sphere.h"
#include "quad.h"

/*
2x + 2y + 2z - 2r = 0
t^2*(dx^2+dy^2+dz^2) +
t*2*(px*dx+py*dy+pz*dz) +
(px^2+py^2+pz^2-r^2)
*/

void		surface_sphere(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hb;
	t_ray		ray;
	t_vec3d		abc;
	FLOAT		t0;
	FLOAT		t1;

	t0 = 2000000;
	t1 = 2000000;
	hb = (t_quad*)quad;
	ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);
	abc.x = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y +
	ray.dir.z * ray.dir.z;
	abc.y = 2 * (ray.pos.x * ray.dir.x + ray.pos.y * ray.dir.y +
	ray.pos.z * ray.dir.z);
	abc.z = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y
	+ ray.pos.z * ray.pos.z - hb->r * hb->r;
	solve_quadratic(&t0, &t1, abc.x, abc.y, abc.z);
	hit_switch(t0, t1, hb->id, hit, &ray);
	return ;
}

void		surface_sphere_normal(void *quad, t_hit *hit)
{
	(void)quad;
	hit->normal.x = 2 * hit->hitpoint.x;
	hit->normal.y = 2 * hit->hitpoint.y;
	hit->normal.z = 2 * hit->hitpoint.z;
	vec_normalize(&hit->normal);
}

t_quad	*surface_default_sphere(t_vec3d *pos)
{
	t_quad	*sphere;

	sphere = (t_quad*)malloc(sizeof(t_quad));
	vec_init(&sphere->matt, pos->x, pos->y, pos->z);
	vec_init(&sphere->matr, 0, 0, 0);
	vec_init(&sphere->mats, 1, 1, 1);
	sphere->a = 0;
	sphere->b = 0;
	sphere->c = 0;
	sphere->r = 150;
	color_init(&sphere->mtl.color, 0.3f, 1.f, 0.3f);
	color_init(&sphere->mtl.specular, 1.0f, 1.0f, 1.0f);
	sphere->mtl.reflect = 0.4;
	return (sphere);
}
