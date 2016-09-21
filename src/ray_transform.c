#include "ray.h"

void	ray_translate(t_ray *ray, FLOAT tx, FLOAT ty, FLOAT tz)
{
	ray->pos.x += tx;
	ray->pos.y += ty;
	ray->pos.z += tz;
}

void	ray_rotate(t_ray *ray, FLOAT rx, FLOAT ry, FLOAT rz)
{
	ray->pos = vec_rotaion_x(&ray->pos, rx);
	ray->pos = vec_rotaion_y(&ray->pos, ry);
	ray->pos = vec_rotaion_z(&ray->pos, rz);
	ray->dir = vec_rotaion_x(&ray->dir, rx);
	ray->dir = vec_rotaion_y(&ray->dir, ry);
	ray->dir = vec_rotaion_z(&ray->dir, rz);
}

void	ray_scale(t_ray *ray, FLOAT tx, FLOAT ty, FLOAT tz)
{
	ray->pos.x *= tx;
	ray->pos.y *= ty;
	ray->pos.z *= tz;
	ray->dir.x *= tx;
	ray->dir.y *= ty;
	ray->dir.z *= tz;
	vec_normalize(&ray->dir);
}

t_ray	ray_invertmat(t_ray *srcray, t_vec3d *matt, t_vec3d *matr, t_vec3d *mats)
{
	t_ray	ray;

	ray = *srcray;
	ray_translate(&ray, -matt->x, -matt->y, -matt->z);
	ray_rotate(&ray, -matr->x, -matr->y, -matr->z);
	(void)mats;
	/*ray_scale(&ray, 1.f / mats->x, 1.f / mats->y, 1.f / mats->z);*/
	return (ray);
}