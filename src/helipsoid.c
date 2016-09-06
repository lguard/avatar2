#include "quad.h"

/*void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit)*/
/*{*/
	/*t_quad		*hb;*/
	/*t_ray		ray;*/
	/*t_vec3d		param;*/
	/*FLOAT		t0 = 2000000;*/
	/*FLOAT		t1 = 2000000;*/

	/*hb = (t_quad*)quad;*/
	/*vec_init(&param, hb->a, hb->b, hb->c);*/
	/*ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);*/
	/*solve_quadraticv2(&t0, &t1, dot_produce_elips(ray.dir, ray.dir, param),*/
	/*2*dot_produce_elips(ray.dir, ray.pos, param) ,*/
	/*dot_produce_elips(ray.pos, ray.pos, param) + hb->r);*/
	/*hit_switch(t0, t1, hb->id, hit, &ray);*/
	/*return ;*/
/*}*/

/*void		surface_hyperboloid_normal(void *quad, t_hit *hit)*/
/*{*/
	/*t_quad	*hb;*/

	/*hb = (t_quad*)quad;*/
	/*hit->normal.x = 2*hit->hitpoint.x *hb->a;*/
	/*hit->normal.y = 2*hit->hitpoint.y *hb->b;*/
	/*hit->normal.z = 2*hit->hitpoint.z *hb->c;*/
	/*vec_normalize(&hit->normal);*/
/*}*/


/*x^2+z^2 = r^2*/
/*(px+dx*t)^2 + (pz+dz*t)^2 = r^2*/
/*t^2*(dx^2+dz^2) + t*2*(px*dx+pz*dz)+ px^2+pz^2 -r^2= 0*/

/*void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit)*/
/*{*/
	/*[>visible<]*/
	/*[>r = 10<]*/
	/*t_quad		*hb;*/
	/*t_ray		ray;*/
	/*t_vec3d		abc;*/
	/*FLOAT		t0 = 2000000;*/
	/*FLOAT		t1 = 2000000;*/

	/*hb = (t_quad*)quad;*/
	/*ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);*/
	/*abc.x = ray.dir.x*ray.dir.x+ray.dir.z*ray.dir.z;*/
	/*abc.y = 2*(ray.pos.x*ray.dir.x+ray.pos.z*ray.dir.z);*/
	/*abc.z = ray.pos.x*ray.pos.x + ray.pos.z*ray.pos.z - hb->r * hb->r; */
	/*solve_quadraticv2(&t0, &t1, abc.x, abc.y, abc.z);*/
	/*hit_switch(t0, t1, hb->id, hit, &ray);*/
	/*return ;*/
/*}*/

/*void		surface_hyperboloid_normal(void *quad, t_hit *hit)*/
/*{*/
	/*t_quad	*hb;*/

	/*hb = (t_quad*)quad;*/
	/*hit->normal.x = 2*hit->hitpoint.x;*/
	/*hit->normal.y = 0;*/
	/*hit->normal.z = 2*hit->hitpoint.z;*/
	/*vec_normalize(&hit->normal);*/
/*}*/

/*x^2*a+z^2*a - y^2*/


/*(t^2)*((dx^2)*a+(dy^2)*b+(dz^2))+*/

/*t*(2*dx*px*a+2*dy*py*b+dz*pz)+*/

/*(px^2)*a+(py^2)*b+(pz^2)*/


void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit)
{
	/*[>visible<]*/
	/*[>a = 2 c= 2<]*/
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

void		surface_hyperboloid_normal(void *quad, t_hit *hit)
{
	t_quad	*hb;

	hb = (t_quad*)quad;
	hit->normal.x = 2*hit->hitpoint.x *hb->a;
	hit->normal.y = -2*hit->hitpoint.y;
	hit->normal.z = 2*hit->hitpoint.z *hb->c;
	vec_normalize(&hit->normal);
}
