#include "quad.h"

/*[>visible<]*/
/*[>a = 2 c= 2<]*/

/*x^2*a+z^2*a - y^2*/


/*(t^2)*((dx^2)*a+(dy^2)*b+(dz^2))+*/

/*t*(2*dx*px*a+2*dy*py*b+dz*pz)+*/

/*(px^2)*a+(py^2)*b+(pz^2)*/

void		surface_cone(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hb;
	t_ray		ray;
	t_vec3d		abc;
	FLOAT		t0 = 2000000;
	FLOAT		t1 = 2000000;

	hb = (t_quad*)quad;
	ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);
	abc.x = ray.dir.x*ray.dir.x*hb->a +
			ray.dir.z*ray.dir.z*hb->c -
			ray.dir.y*ray.dir.y;

	abc.y = 2*ray.pos.x*ray.dir.x*hb->a +
			2*ray.pos.z*ray.dir.z*hb->c -
			2*ray.pos.y*ray.dir.y;

	abc.z = ray.pos.x*ray.pos.x*hb->a + 
			ray.pos.z*ray.pos.z*hb->c -
			ray.pos.y*ray.pos.y; 

	solve_quadraticv2(&t0, &t1, abc.x, abc.y, abc.z);
	hit_switch(t0, t1, hb->id, hit, &ray);
	return ;
}

void		surface_cone_normal(void *quad, t_hit *hit)
{
	t_quad	*hb;

	hb = (t_quad*)quad;
	hit->normal.x = 2*hit->hitpoint.x *hb->a;
	hit->normal.y = -2*hit->hitpoint.y;
	hit->normal.z = 2*hit->hitpoint.z *hb->c;
	vec_normalize(&hit->normal);
}
