#include "object.h"

void	hit_error(t_ray *ray, void *non, t_hit *hit)
{
	(void)ray;
	(void)non;
	(void)hit;
	print("Error: can't select object function %s\n", __FILE__);
}
