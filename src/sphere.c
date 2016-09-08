#include "sphere.h"
#include "quad.h"

FLOAT	dot_produce_elips2(t_vec3d a, t_vec3d b, t_vec3d c)
{
	return a.x*b.x*c.x+a.y*b.y*c.y+a.z*b.z*c.z;
}

FLOAT	solve_quadratic(FLOAT a, FLOAT b, FLOAT c)
{
	FLOAT	t0;
	FLOAT	t1;
	FLOAT	d;

	d = b*b - 4*a * c;
	if (d < 0.0f)
		return 1000000;
	t0 = (-b + sqrtf(d)) / (2*a);
	t1 = (-b - sqrtf(d)) / (2*a);

	if (t0 < t1) {
		return t0;
	}
	else {
		return t1;
	}
}

/*void	solve_quadratic(FLOAT *t0, FLOAT *t1, FLOAT a, FLOAT b, FLOAT c)*/
/*{*/
	/*FLOAT	d;*/

	/*d = b*b - 4*a * c;*/
	/*if (d < 0.0f)*/
		/*return ;*/
	/**t0 = (-b + sqrtf(d)) / (2*a);*/
	/**t1 = (-b - sqrtf(d)) / (2*a);*/
/*}*/

void		hit_sphere(t_ray *ray, void *sphere, t_hit *hit)
{
	FLOAT		t0;
	FLOAT		t1;
	FLOAT		b;
	FLOAT		d;
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
	hit->reflect = s->mtl.reflect;
	hit->normal = hit_normal(ray, s, hit);
	hit->id = s->id;
	return ;
}
// todo: metre toute les fonction de normal dans des list pour eviter de les calculer 2 fois
t_vec3d		hit_normal(t_ray *ray, t_sphere *s, t_hit *hit)
{

				/*2x + 2y + 2z - 2r = 0*/
	hit->hitpoint = vec_scale(&ray->dir, hit->t);
	hit->hitpoint = vec_add(&hit->hitpoint, &ray->pos);
	t_vec3d		normal = vec_sub(&hit->hitpoint, &s->pos);
	vec_normalize(&normal);
	return normal;
}

void		hit_sphere2(t_ray *srcray, void *sphere, t_hit *hit)
{
	FLOAT		t0;
	FLOAT		t1;
	FLOAT		b;
	FLOAT		d;
	t_vec3d		r;
	t_sphere2	*s;
	t_ray		ray;

	t_vec3d	test = {0.0002, -0.0002, 0.0002};
	s = (t_sphere2*)sphere;
	ray = ray_invertmat(srcray, &s->matt, &s->matr, &s->mats);
	r = vec_sub(&s->pos, &ray.pos);
	b = vec_dotproduct(&ray.dir, &r);
	(void)b;
	(void)r;
	(void)d;
	(void)t1;
	/*t²*(X²*A+Y²*B+Z²*C)+t*2*(X*A*px+Y*B*py+Z*C*pz)+ A*px² + B*py² + C*pz² - 1 = 0*/
	/*t0 = solve_quadratic(vec_dotproduct(&ray.dir, &ray.dir), 2 * vec_dotproduct(&ray.dir, &ray.pos),vec_dotproduct(&ray.pos, &ray.pos)- s->radius * s->radius);*/
	t0 = solve_quadratic(dot_produce_elips2(ray.dir, ray.dir, test), 2*dot_produce_elips2(ray.dir, ray.pos, test)
	,dot_produce_elips2(ray.pos, ray.pos, test)- 1);
	if (t0 > 0.1f && t0 < hit->t) {
		/*t_vec3d tt = vec_scale(&ray.dir, t0);*/
		/*tt = vec_add(&tt, &ray.pos);*/
		/*if (tt.x >10 || tt.y >10 || tt.z >10)*/
			/*return;*/
		hit->t = t0;
	}
	else {
		return ;
	}
	/*d = b*b - vec_dotproduct(&r, &r) + s->radius * s->radius;*/
	/*if (d < 0.0f)*/
		/*return ;*/
	/*t0 = b - sqrtf(d); */
	/*t1 = b + sqrtf(d);*/
	/*if (t0 > 0.1f && t0 < t1 && t0 < hit->t) {*/
		/*hit->t = t0;*/
	/*}*/
	/*else if (t1 > 0.1f && t1 < hit->t) {*/
		/*hit->t = t1;*/
	/*}*/
	/*else {*/
		/*return ;*/
	/*}*/
	hit->didit = 1;
	hit->mtl = &s->mtl;
	hit->dir = srcray->dir;
	hit->reflect = s->mtl.reflect;
	hit->normal = hit_normal2(&ray, s, hit);
	hit->id = s->id;
	/*vec_matscale(&hit->hitpoint, s->mats.x, s->mats.y, s->mats.z);*/
	/*vec_matscale(&hit->normal, 1/s->mats.x, 1/s->mats.y, 1/s->mats.z);*/
	hit->normal.x = 2*hit->hitpoint.x *test.x;
	hit->normal.y = 2*hit->hitpoint.y *test.y;
	hit->normal.z = 2*hit->hitpoint.z *test.z;
	vec_normalize(&hit->normal);
	vec_rotate(&hit->hitpoint, s->matr.x, s->matr.y, s->matr.z);
	vec_rotate(&hit->normal, s->matr.x, s->matr.y, s->matr.z);
	vec_translate(&hit->hitpoint, s->matt.x, s->matt.y, s->matt.z);
	return ;
}

t_vec3d		hit_normal2(t_ray *ray, t_sphere2 *s, t_hit *hit)
{
	hit->hitpoint = vec_scale(&ray->dir, hit->t);
	hit->hitpoint = vec_add(&hit->hitpoint, &ray->pos);
	t_vec3d		normal = vec_sub(&hit->hitpoint, &s->pos);
	vec_normalize(&normal);
	return normal;
}

/*t^2*(dx^2+dy^2+dz^2) +*/
/*t*2*(px*dx+py*dy+pz*dz) +*/
/*(px^2+py^2+pz^2-r^2)*/

void		surface_sphere(t_ray *srcray, void *quad, t_hit *hit)
{
	t_quad		*hb;
	t_ray		ray;
	t_vec3d		abc;
	FLOAT		t0 = 2000000;
	FLOAT		t1 = 2000000;

	hb = (t_quad*)quad;
	ray = ray_invertmat(srcray, &hb->matt, &hb->matr, &hb->mats);
	abc.x = ray.dir.x*ray.dir.x + ray.dir.y*ray.dir.y + ray.dir.z*ray.dir.z;
	abc.y = 2 * (ray.pos.x*ray.dir.x + ray.pos.y*ray.dir.y + ray.pos.z*ray.dir.z);
	abc.z = ray.pos.x*ray.pos.x + ray.pos.y*ray.pos.y + ray.pos.z*ray.pos.z - hb->r*hb->r;
	solve_quadraticv2(&t0, &t1, abc.x, abc.y, abc.z);
	hit_switch(t0, t1, hb->id, hit, &ray);
	return ;
}

void		surface_sphere_normal(void *quad, t_hit *hit)
{
	t_quad	*hb;

	hb = (t_quad*)quad;
	hit->normal.x = 2*hit->hitpoint.x;
	hit->normal.y = 2*hit->hitpoint.y;
	hit->normal.z = 2*hit->hitpoint.z;
	vec_normalize(&hit->normal);
}

t_quad	*surface_default_sphere(t_vec3d *pos)
{
	t_quad	*sphere;

	sphere  = (t_quad*)malloc(sizeof(t_quad));
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
