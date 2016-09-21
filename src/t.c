#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "vec.h"
#include "cam.h"
#include "scene.h"
#include "sphere.h"
#include "ray.h"
#include "raytrace.h"
#include "light.h"
#include "mysdl.h"
#include "mtl.h"
#include "buffer.h"
#include "quad.h"

void	write_byte(unsigned char b, int fd)
{
	write(fd, &b, 1);
}

void	write_tga_header(int fd, t_scene *scene, t_color **src)
{
	int width = scene->render_width ;
	int height = scene->render_height;
	write_byte(0,fd);
	write_byte(0,fd);
	write_byte(2,fd);                 //        [> uncompressed RGB <]
	write_byte(0,fd); write_byte(0,fd);
	write_byte(0,fd); write_byte(0,fd);
	write_byte(0,fd);
	write_byte(0,fd); write_byte(0,fd);//           [> X origin <]
	write_byte(0,fd); write_byte(0,fd);//           [> y origin <]
	write_byte((width & 0x00FF),fd);
	write_byte((width & 0xFF00) / 256,fd);
	write_byte((height & 0x00FF),fd);
	write_byte((height & 0xFF00) / 256,fd);
	write_byte(24,fd);//                        [> 24 bit bitmap <]
	write_byte(0,fd);

	for (int y = 0 ; y < height;++y) {
		for (int x = 0 ; x < width;++x) {
				write_byte((unsigned char)(src[x][y].b*255.0f),fd);
				write_byte((unsigned char)(src[x][y].g*255.0f),fd);
				write_byte((unsigned char)(src[x][y].r*255.0f),fd);
		}
	}
}

	/*int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);*/
	/*write_tga_header(fd, &scene, buff.a);*/
	/*close(fd);*/

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

void		foreach_light(t_scene *sc, t_hit *hit, t_color *colora, FLOAT rc)
{
	t_list	*ptr;
	t_color colorb;

	ptr = sc->light;
	color_init(&colorb, 0, 0, 0);
	while (ptr)
	{
		dotlight(&colorb, (t_dotlight*)ptr->data, hit, sc);
		ptr = ptr->next;
	}
	color_scale(&colorb, (rc * (1 - hit->mtl->reflect)));
	color_add(colora, &colorb);
}

void		light_and_reflect(t_ray *ray, t_hit *hit, t_scene *sc, t_color *colora)
{
	int		i;
	FLOAT	rc;

	i = sc->reflect;
	rc = 1.f;
	color_init(colora, 0, 0, 0);
	while(i != 0)
	{
		hit->dir = ray->dir;
		hit->raypos = ray->pos;
		ray_trace(ray, sc->obj, hit);
		if (!hit->didit)
			return ;
		process_hit(hit, sc->obj);
		foreach_light(sc, hit, colora, rc);
		if (!(sc->opti & REFLECTION))
			return ;
		rc *= hit->mtl->reflect;
		ray->dir = vec_reflect(&ray->dir, &hit->normal);
		ray->pos = hit->hitpoint;
		hit_clear(hit);
		--i;
	}
}

void	pbar2(t_scene *sc)
{
	if (sc->progressbar)
	{
		sc->progressbar = 0;
		print("\n");
	}
}

void	pbar(int x, int y, t_scene *sc)
{
	if (sc->progressbar)
	{
		print("\rprogress: %%%d       ",
		(int)(((FLOAT)(x * sc->height +y) /
		(FLOAT)(sc->height * sc->width)) * 100.f));
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

void	single_rt(t_scene *scene, int x, int y)
{
	t_hit hit;
	t_ray ray;
	FLOAT xindent;
	FLOAT yindent;
	t_color color;

	xyratio(&xindent, &yindent, &scene->cam, scene->width, scene->height);
	t_vec3d planepix = getplanepix(&scene->cam, x/2, y/2, xindent, yindent);
	hit.t = 20000;
	hit.didit = 0;
	vec_normalize(&planepix);
	vec_init(&ray.dir, planepix.x, planepix.y, planepix.z);
	vec_init(&ray.pos, scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);

	light_and_reflect(&ray, &hit, scene, &color);
	print("\033[48;2;%d;%d;%dm", (unsigned char)(color.r*255.0f), (unsigned char)(color.g*255.0f), (unsigned char)(color.b*255.0f));
	print("x:%d, y:%d | r:%d g:%d b:%d\033[0m\n", x, y, (unsigned char)(color.r*255.0f), (unsigned char)(color.g*255.0f), (unsigned char)(color.b*255.0f));
}

void	render(t_env *e, t_scene *scene, t_color **a)
{
	int x;
	int y;
	
	x = 0;
	while(x < scene->render_width)
	{
		y = 0;
		while(y < scene->render_height)
		{
			sdl_putpxl(e, x, y,
			(unsigned char)(a[x][y].r*255.0f),
			(unsigned char)(a[x][y].g*255.0f),
			(unsigned char)(a[x][y].b*255.0f));
			++y;
		}
		++x;
	}
}


void	init_scene(t_scene *scene, int width, int height)
{
	vec_init(&scene->cam.pos, 350.f, 10.f, -3000.f);
	vec_init(&scene->cam.dirvec, 0.f, 0.f, 1.f);
	vec_init(&scene->cam.upvec, 0.f, 1.f, 0.f);
	scene->cam.rightvec = vec_mul(&scene->cam.dirvec, &scene->cam.upvec);
	scene->render_width = width;
	scene->render_height = height;
	scene->width = scene->render_width * 1;
	scene->height = scene->render_height * 1;
	scene->cam.wfov = 1.0;
	scene->cam.hfov = 1.0 / ((float)width / (float)height);
	scene->cam.viewplane_upleft = getupleft(&scene->cam, scene->cam.wfov, scene->cam.hfov);
	scene->cam.distance = 1.f;
	scene->cam.roty = 0;
	scene->cam.rotx = 0;
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
