#include "raytrace.h"
#include "ray.h"

void	ray_trace(t_ray *ray, t_list *obj, t_hit *hit)
{
	while (obj)
	{
		((t_obj*)(obj->data))->hit(ray, ((t_obj*)(obj->data))->object, hit);
		obj = obj->next;
	}
}
