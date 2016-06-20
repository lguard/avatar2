#ifndef SPHERE_H
# define SPHERE_H

# include "vec.h"
# include "ray.h"
# include "math.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_sphere
{
	t_vec3d	pos;
	FLOAT	radius;
	t_mtl	mtl;
	int		id;
}				t_sphere;

typedef struct	s_sphere2
{
	t_vec3d	pos;
	FLOAT	radius;
	t_mtl	mtl;
	int		id;
	t_vec3d	matt;
	t_vec3d	matr;
	t_vec3d	mats;
}				t_sphere2;

void		hit_sphere(t_ray *ray, void *sphere, t_hit *hit);
t_vec3d		hit_normal(t_ray *ray, t_sphere *s, t_hit *hit);
t_vec3d		hit_normal2(t_ray *ray, t_sphere2 *s, t_hit *hit);
void		hit_sphere2(t_ray *srcray, void *sphere, t_hit *hit);

#endif /* SPHERE_H */
