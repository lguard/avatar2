#ifndef RAY_H
# define RAY_H

#include "vec.h"
#include "list.h"
#include "mtl.h"

typedef struct	s_ray
{
	t_vec3d	pos;
	t_vec3d	dir;
}				t_ray;

typedef struct	s_hit
{
	char	didit;
	double	t;
	t_vec3d	dir;
	t_vec3d	normal;
	t_vec3d	hitpoint;
	t_mtl	*mtl;
	int		id;
}				t_hit;

#endif /* RAY_H */
