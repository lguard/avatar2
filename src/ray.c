#include "raytrace.h"
#include "ray.h"

void	ray_trace(t_ray *ray, t_list *obj, t_hit *hit)
{
	while (obj)
	{
		(void)hit;
		(void)ray;
		((t_obj*)(obj->data))->hit(ray, ((t_obj*)(obj->data))->object, hit);
		obj = obj->next;
	}
}

inline void	hit_switch(FLOAT t0, FLOAT t1, int id, t_hit *hit, t_ray *ray)
{
	if (t0 > 0.1f && t0 < t1 && t0 < hit->t)
	{
		hit->t = t0;
	}
	else if (t1 > 0.1f && t1 < hit->t)
	{
		hit->t = t1;
	}
	else
	{
		return ;
	}
	hit->id = id;
	hit->didit = 1;
	hit->dir = ray->dir;
	hit->raypos = ray->pos;
}

inline void	hit_clear(t_hit *hit)
{
	hit->didit = 0;
	hit->t = 2000000;
}

uint16_t	get_id(void)
{
	static uint16_t i = 0;

	return (i++);
}
