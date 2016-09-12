#include "quad.h"

/*[>visible<]*/
/*[>r = 10<]*/

/*x^2+z^2 = r^2*/
/*(px+dx*t)^2 + (pz+dz*t)^2 = r^2*/
/*t^2*(dx^2+dz^2) + t*2*(px*dx+pz*dz)+ px^2+pz^2 -r^2= 0*/

void		surface_cylindre(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hb;
	t_ray		ray;
	t_vec3d		abc;
	FLOAT		t0 = 2000000;
	FLOAT		t1 = 2000000;

	hb = (t_quad*)quad;
	ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);
	abc.x = ray.dir.x*ray.dir.x+ray.dir.z*ray.dir.z;
	abc.y = 2*(ray.pos.x*ray.dir.x+ray.pos.z*ray.dir.z);
	abc.z = ray.pos.x*ray.pos.x + ray.pos.z*ray.pos.z - hb->r * hb->r; 
	solve_quadraticv2(&t0, &t1, abc.x, abc.y, abc.z);
	hit_switch(t0, t1, hb->id, hit, &ray);
	return ;
}

void		surface_cylindre_normal(void *quad, t_hit *hit)
{
	(void)quad;
	hit->normal.x = 2*hit->hitpoint.x;
	hit->normal.y = 0;
	hit->normal.z = 2*hit->hitpoint.z;
	vec_normalize(&hit->normal);
}

t_quad	*surface_default_cylindre(t_vec3d *pos)
{
	t_quad	*sphere;

	sphere  = (t_quad*)malloc(sizeof(t_quad));
	vec_init(&sphere->matt, pos->x, pos->y, pos->z);
	vec_init(&sphere->matr, 0, 0, 0);
	vec_init(&sphere->mats, 1, 1, 1);
	sphere->a = 0;
	sphere->b = 0;
	sphere->c = 0;
	sphere->r = 100;
	color_init(&sphere->mtl.color, 0.0f, 0.3f, 1.0f);
	color_init(&sphere->mtl.specular, 1.0f, 1.0f, 1.0f);
	sphere->mtl.reflect = 0;
	return (sphere);
}
