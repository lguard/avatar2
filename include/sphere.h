#ifndef SPHERE_H
# define SPHERE_H

# include "vec.h"
# include "ray.h"

typedef struct	s_sphere
{
	t_vec3d	pos;
	double	radius;
}				t_sphere;

int		hit_sphere(t_ray *ray, void *sphere);

#endif /* SPHERE_H */
