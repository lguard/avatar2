#include "sphere.h"


/*
	ray		:	ray = c.pos + c.dir * t
	sphere	:	x² + y² + z² = r²
			:	(c.pos.x + c.dir.x *t)² + (c.pos.y + c.dir.y *t)² + (c.pos.z + c.dir.z *t)² = r²
				(   a    +     b     )² = a² + 2ab + b²
				c.dir²*t² + 2*c.dir*c.pos*t + c.pos² for x y z

				(c.dir.x² + c.dir.y² + c.dir.z²)*t² +
				2*(c.pos.x*c.dir.x+c.pos.y*c.dir.y+c.pos.z*c.dir.z)*t +
				(c.pos.x² + c.pos.y² + c.pos.z²) = r²

				(c.dir.x² + c.dir.y² + c.dir.z²)*t² +
				2*(c.pos.x*c.dir.x+c.pos.y*c.dir.y+c.pos.z*c.dir.z)*t +
				(c.pos.x² + c.pos.y² + c.pos.z² + r²) = 0

				o.pos = s.pos - c.pos
				position de la camera - centre de la sphere pour deplacer l'origin

				(c.dir.x² + c.dir.y² + c.dir.z²)*t² +
				2*(o.pos.x*c.dir.x+o.pos.y*c.dir.y+o.pos.z*c.dir.z)*t +
				(o.pos.x² + o.pos.y² + o.pos.z² + r²) = 0
	elipsoid:
				x²/a² + y²/b² + z²/c² = 1
				A = 1 / a²; B = 1 / b² ;C = 1 / c²
				X = dx; Y = dy; Z = dz; 
				(X*t)²*A + (Y*t)²*B + (Z*t)²*C = 1
				X²*t²*A + 2*X*t*A+
				Y²*t²*B + 2*Y*t*B+
				Z²*t²*C + 2*Z*t*C
				t²*(X²*A+Y²*B+Z²*C)+t*2*(X*A+Y*B+Z*C) = 1
	hyperboloide:
				x²/a² + y²/b² - z²/c² = 1
*/

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

	s = (t_sphere2*)sphere;
	ray = ray_invertmat(srcray, &s->matt, &s->matr, &s->mats);
	r = vec_sub(&s->pos, &ray.pos);
	b = vec_dotproduct(&ray.dir, &r);
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
	hit->dir = srcray->dir;
	hit->reflect = s->mtl.reflect;
	hit->normal = hit_normal2(&ray, s, hit);
	hit->id = s->id;
	vec_matscale(&hit->hitpoint, s->mats.x, s->mats.y, s->mats.z);
	vec_matscale(&hit->normal, 1/s->mats.x, 1/s->mats.y, 1/s->mats.z);
	/*vec_rotate(&hit->hitpoint, s->matr.x, s->matr.y, s->matr.z);*/
	/*vec_rotate(&hit->normal, s->matr.x, s->matr.y, s->matr.z);*/
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
