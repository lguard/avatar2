#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "object.h"
#include "ray.h"

void		ray_trace(t_ray *ray, t_list *obj, t_hit *hit);

#endif /* RAYTRACE_H */
