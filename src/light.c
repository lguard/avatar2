#include "light.h"

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_color color)
{
	light->pos = pos;
	light->color = color;
}

void	dotlight(t_color *color, t_dotlight *light, t_hit *hit, t_list *objlst, int opti)
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
	ray.dir = vec_scale(&dist, (1.0f/hitshadow.t));
	ray_trace(&ray, objlst, &hitshadow);
	if (!hitshadow.didit)
	{
		if (opti & DIFFUSE)
		{
			FLOAT lambert = vec_dotproduct(&ray.dir, &hit->normal);
			color->r = MIN(1.0f, color->r+ lambert * light->color.r * hit->mtl->color.r);
			color->g = MIN(1.0f, color->g+ lambert * light->color.g * hit->mtl->color.g);
			color->b = MIN(1.0f, color->b+ lambert * light->color.b * hit->mtl->color.b);
		}
		if (opti & SPECULAR)
		{
			t_vec3d phongDir = vec_reflect(&ray.dir, &hit->normal);
			FLOAT phongTerm = MAX(vec_dotproduct(&phongDir, &hit->dir), 0.0f) ;
			phongTerm = 1.f * powf(phongTerm, 60.f);
			color->r= MIN(1.f, color->r + phongTerm * light->color.r * hit->mtl->specular.r);
			color->g= MIN(1.f, color->g + phongTerm * light->color.g * hit->mtl->specular.g);
			color->b= MIN(1.f, color->b + phongTerm * light->color.b * hit->mtl->specular.b);
		}
	}
}

void	addolight(t_list **lightlist, t_dotlight *light)
{
	t_dotlight	*new;

	new = (t_dotlight*)malloc(sizeof(t_dotlight));
	memcpy(new, light, sizeof(t_dotlight));
	list_pushfront(lightlist, (void*)new);
}

void	delete_light(void *obj)
{
	(void)obj;
	free(obj);
}
