#include "sphere.h"

/*int		hit_sphere(t_ray *ray, void *sphere)*/
/*{*/
	/*double		b;*/
	/*double		c;*/
	/*double		delta;*/
	/*t_vec3d		r;*/
	/*t_sphere	*s;*/

	/*s = (t_sphere*)sphere;*/
	/*r = vec_sub(&ray->pos, &s->pos);*/
	/*b = vec_dotproduct(&r, &ray->dir);*/
	/*c = vec_getsquare_length(&r) - (s->radius * s->radius);*/
	/*delta = (b*b) - c;*/

	/*if (delta < 0.0f)*/
		/*return (0);*/
	/*return (1);*/
/*}*/

int		hit_sphere(t_ray *ray, void *sphere)
{
	double		b;
	double		d;
	t_vec3d		r;
	t_sphere	*s;

	s = (t_sphere*)sphere;
	r = vec_sub(&s->pos, &ray->pos);
	b = vec_dotproduct(&ray->dir, &r);
	d = b*b - vec_dotproduct(&r, &r) + s->radius * s->radius;
	if (d < 0.0f)
		return (0);
	return (1);
}
