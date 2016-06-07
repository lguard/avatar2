#ifndef SPHERE_H
# define SPHERE_H

# include "vec.h"
# include "ray.h"
# include "math.h"
# include "mtl.h"

typedef struct	s_sphere
{
	t_vec3d	pos;
	double	radius;
	t_mtl	mtl;
	int		id;
}				t_sphere;

void		hit_sphere(t_ray *ray, void *sphere, t_hit *hit);
t_vec3d		hit_normal(t_ray *ray, t_sphere *s, t_hit *hit);

#endif /* SPHERE_H */
