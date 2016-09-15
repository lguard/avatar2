#include "quad.h"

void	solve_quadraticv2(FLOAT *t0, FLOAT *t1, FLOAT a, FLOAT b, FLOAT c)
{
	FLOAT	d;

	d = b * b - 4 * a * c;
	if (d < 0.0f)
		return ;
	*t0 = (-b + sqrtf(d)) / (2 * a);
	*t1 = (-b - sqrtf(d)) / (2 * a);
}

FLOAT	dot_produce_elips(t_vec3d a, t_vec3d b, t_vec3d c)
{
	return (a.x * b.x * c.x + a.y * b.y * c.y + a.z * b.z * c.z);
}
