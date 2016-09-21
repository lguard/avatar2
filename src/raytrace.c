#include "raytrace.h"

void	process_hit(t_hit *hit, t_list *objlist)
{
	t_obj		*obj;
	t_obj_header	*idobj;
	
	obj = getobject_by_id(hit->id, objlist);
	idobj = (t_obj_header*)obj->object;

	hit->mtl = &(idobj->mtl);
	hit->hitpoint = vec_scale(&hit->dir, hit->t);
	hit->hitpoint = vec_add(&hit->hitpoint, &hit->raypos);
	obj->normal(obj->object, hit);
	vec_rotate(&hit->hitpoint, idobj->matr.x, idobj->matr.y, idobj->matr.z);
	vec_rotate(&hit->normal, idobj->matr.x, idobj->matr.y, idobj->matr.z);
	vec_translate(&hit->hitpoint, idobj->matt.x, idobj->matt.y, idobj->matt.z);
}

void		foreach_light(t_scene *sc, t_hit *hit, t_color *cla, FLOAT rc)
{
	t_list	*ptr;
	t_color clb;

	ptr = sc->light;
	color_init(&clb, 0, 0, 0);
	while (ptr)
	{
		dotlight(&clb, (t_dotlight*)ptr->data, hit, sc);
		ptr = ptr->next;
	}
	color_scale(&clb, (rc * (1 - hit->mtl->reflect)));
	color_add(cla, &clb);
}

void		light_and_reflect(t_ray *ray, t_hit *hit, t_scene *sc, t_color *cla)
{
	int		i;
	FLOAT	rc;

	i = sc->reflect;
	rc = 1.f;
	color_init(cla, 0, 0, 0);
	while(i != 0)
	{
		hit->dir = ray->dir;
		hit->raypos = ray->pos;
		ray_trace(ray, sc->obj, hit);
		if (!hit->didit)
			return ;
		process_hit(hit, sc->obj);
		foreach_light(sc, hit, cla, rc);
		if (!(sc->opti & REFLECTION))
			return ;
		rc *= hit->mtl->reflect;
		ray->dir = vec_reflect(&ray->dir, &hit->normal);
		ray->pos = hit->hitpoint;
		hit_clear(hit);
		--i;
	}
}


void	rt(t_scene *sc, t_color **a)
{
	t_vec3d	pps[2];
	t_hit	hit;
	t_ray	ray;
	int		x;
	int		y;

	x = 0;
	xyratio(&pps[0].x, &pps[0].y, &sc->cam, sc->width, sc->height);
	while(x < sc->width)
	{
		y = 0;
		while(y < sc->height)
		{
			pps[1] = getplanepix(&sc->cam, x, y, pps[0].x, pps[0].y);
			hit_clear(&hit);
			vec_init(&ray.dir, pps[1].x, pps[1].y, pps[1].z);
			vec_init(&ray.pos, sc->cam.pos.x, sc->cam.pos.y, sc->cam.pos.z);
			light_and_reflect(&ray, &hit, sc, &a[x][y]);
			++y;
		}
		pbar(x, y, sc);
		++x;
	}
	pbar2(sc);
}

int mainrt(t_env *e, t_scene *scene, t_buffer *buff)
{
	if (scene->opti & UNDERSAMPLE)
	{
		rt(scene, buff->c);
		buffer_us(buff);
		render(e, scene, buff->a);
	}
	else if (buff->aa == 1)
	{
		rt(scene, buff->b);
		render(e, scene, buff->b);
	}
	else
	{
		rt(scene, buff->b);
		buffer_ss(buff);
		render(e, scene, buff->a);
	}
	return 0;
}
