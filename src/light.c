#include "light.h"

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_color color)
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

void	dotlight(t_color *color, t_dotlight *light, t_hit *hit, t_list *objlst)
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
		color->r = min(1.0f, color->r+ lambert * light->color.r * hit->mtl->color.r);
		color->g = min(1.0f, color->g+ lambert * light->color.g * hit->mtl->color.g);
		color->b = min(1.0f, color->b+ lambert * light->color.b * hit->mtl->color.b);

		float phongTerm = max(vec_dotproduct(&phongDir, &hit->dir), 0.0f) ;
		phongTerm = 1.f * powf(phongTerm, 60.f);
		color->r= min(1.f, color->r + phongTerm * light->color.r);
		color->g= min(1.f, color->g + phongTerm * light->color.g);
		color->b= min(1.f, color->b + phongTerm * light->color.b);
	}
}
