#ifndef PLANE_H
# define PLANE_H

# include "vec.h"
# include "ray.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_plane
{
	t_vec3d		normal;
	t_vec3d		pos;
	t_mtl	mtl;
	int		id;
}				t_plane;

void	hit_plane(t_ray *ray, void *plane, t_hit *hit);

#endif /* PLANE_H */
