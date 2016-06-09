#include "light.h"

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_vec3d color)
{
	light->pos = pos;
	light->color = color;
}

double	min(double a, double b)
{
	if (a < b)
		return a;
	return b;
}

double	max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

void	dotlight(t_vec3d *color, t_dotlight *light, t_hit *hit, t_list *objlst)
{
	t_hit	hitshadow;
	t_ray	ray;

	hitshadow.didit = 0;
	ray.pos = hit->hitpoint;
	t_vec3d	dist = vec_sub(&light->pos, &hit->hitpoint);
	if (vec_dotproduct(&hit->normal, &dist) <= 0.0f)
		return ;
	hitshadow.t = sqrtf(vec_dotproduct(&dist, &dist));
	if (hitshadow.t <= 0.f)
		return ;
	t_vec3d lightdir = vec_scale(&dist, (1.0f/hitshadow.t));
	/*ray.dir = vec_sub(&light->pos, &hit->hitpoint);*/
	/*vec_normalize(&ray.dir);*/
	ray.dir = lightdir;
	ray_trace(&ray, objlst, &hitshadow);
	if (!hitshadow.didit)
	{
		t_vec3d phongDir = vec_reflect(&ray.dir, &hit->normal);
		double lambert = vec_dotproduct(&lightdir, &hit->normal);
		color->x = min(1.0f, color->x+ lambert * light->color.x * hit->mtl->color.r);
		color->y = min(1.0f, color->y+ lambert * light->color.y * hit->mtl->color.g);
		color->z = min(1.0f, color->z+ lambert * light->color.z * hit->mtl->color.b);

		float phongTerm = max(vec_dotproduct(&phongDir, &hit->dir), 0.0f) ;
		phongTerm = 1.f * powf(phongTerm, 60.f);
		color->x= min(1.f, color->x + phongTerm * light->color.x);
		color->y= min(1.f, color->y + phongTerm * light->color.y);
		color->z= min(1.f, color->z + phongTerm * light->color.z);
	}
}
