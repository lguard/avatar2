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

#define DEGREESTORADIANS(x) (x * M_PI / 180.0)
#define RADIANSTODEGREES(x) (x * 180.0 / M_PI)

void		AA(t_color **src, t_color **rcv, size_t x, size_t y)
{
	for (size_t i = 1;i<(x-1);++i) {
		for (size_t j = 1;j<(y-1);++j) {
			rcv[i][j].r = (src[i-1][j-1].r+
						src[i-1][j].r+
						src[i-1][j+1].r+
						src[i][j-1].r+
						src[i][j+1].r+
						src[i+1][j-1].r+
						src[i+1][j].r+
						src[i+1][j+1].r + src[i][j].r*2) / 10;
			rcv[i][j].g = (src[i-1][j-1].g+
						src[i-1][j].g+
						src[i-1][j+1].g+
						src[i][j-1].g+
						src[i][j+1].g+
						src[i+1][j-1].g+
						src[i+1][j].g+
						src[i+1][j+1].g + src[i][j].g*2) / 10;
			rcv[i][j].b = (src[i-1][j-1].b+
						src[i-1][j].b+
						src[i-1][j+1].b+
						src[i][j-1].b+
						src[i][j+1].b+
						src[i+1][j-1].b+
						src[i+1][j].b+
						src[i+1][j+1].b + src[i][j].b*2) / 10;
		}
	}
}

t_color		**create_buffer(size_t x, size_t y)
{
	t_color		*b = (t_color*)malloc(sizeof(t_color) * x * y);
	t_color		**a = (t_color**)malloc(sizeof(t_color*) * x);
	for (size_t i = 0;i < x;++i) {
		a[i] = b + i*y;
	}
	return a;
}

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

void		light_and_reflect(t_ray *ray, t_hit *hit, t_scene *scene, t_color *colora, int opti)
{
	t_color colorb;
	t_list	*ptr;
	FLOAT	rc;

	color_init(colora, 0, 0, 0);
	rc = 1.f;
	int i = 2;
	while(i != 0)
	{
		color_init(&colorb, 0, 0, 0);
		hit->dir = ray->dir;
		hit->raypos = ray->pos;
		ray_trace(ray, scene->obj, hit);
		if (!hit->didit)
			return ;
		process_hit(hit, scene->obj);
		ptr = scene->light;
		while (ptr) {
			dotlight(&colorb, (t_dotlight*)ptr->data, hit, scene->obj, opti);
			ptr = ptr->next;
		}
		color_scale(&colorb, (rc * (1- hit->mtl->reflect)));
		color_add(colora, &colorb);
		if (!(opti & REFLECTION))
			return ;
		rc *= hit->mtl->reflect;
		ray->dir = vec_reflect(&ray->dir, &hit->normal);
		ray->pos = hit->hitpoint;
		hit->didit = 0;
		--i;
	}
}

void	rt(t_scene *scene, t_color **a, int opti)
{
	t_hit hit;
	t_ray ray;
	FLOAT xindent;
	FLOAT yindent;
	int x=0;
	int y;

	xyratio(&xindent, &yindent, &scene->cam, scene->width, scene->height);
	while(x < scene->width) {
		y =0;
		while(y < scene->height) {
			t_vec3d planepix = getplanepix(&scene->cam, x, y, xindent, yindent);
			hit.t = 20000;
			hit.didit = 0;
			vec_normalize(&planepix);
			vec_init(&ray.dir, planepix.x, planepix.y, planepix.z);
			vec_init(&ray.pos, scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
			light_and_reflect(&ray, &hit, scene, &a[x][y], opti);
			++y;
		}
		++x;
	}
	vec_display(&scene->cam.pos);
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

	light_and_reflect(&ray, &hit, scene, &color, 1 | 64);
	printf("x:%d, y:%d\n", x, y);
	printf("\033[38;2mr %d, g %d, b %d\n", (unsigned char)(color.r*255.0f), (unsigned char)(color.g*255.0f), (unsigned char)(color.b*255.0f));
}

void	render(t_env *e, t_scene *scene, t_color **a)
{
	int x = 0;
	int y;
	
	while(x < scene->render_width) {
		y = 0;
		while(y < scene->render_height) {
				sdl_putpxl(e, x, y, (unsigned char)( a[x][y].r*255.0f), (unsigned char)( a[x][y].g*255.0f), (unsigned char)( a[x][y].b*255.0f));
				++y;
		}
		++x;
	}
}

void	init_sphere(t_scene *sc, FLOAT radius, t_vec3d pos, t_mtl mtl)
{
	static int i = 0;
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	s->pos = pos;
	s->radius = radius;
	s->mtl = mtl;
	s->id = i;
	addobject(&sc->obj, s, 's');
	++i;
}

void	init_plane(t_scene *sc, t_vec3d norm, t_vec3d pos, t_mtl mtl)
{
	static int i = 0;
	t_plane	*p;

	p = malloc(sizeof(t_plane));
	p->pos = pos;
	p->normal = norm;
	vec_normalize(&p->normal);
	p->mtl = mtl;
	p->id = i;
	addobject(&sc->obj, p, 'p');
	++i;
}

void	init_scene(t_scene *scene, int width, int height)
{
	t_dotlight	light;
	t_dotlight	light2;
	t_mtl		mtl;
	/*t_sphere2	*s2;*/
	t_quad		*hyper;
	t_quad		*hyper2;
	t_plane		*plane;
	t_plane		*plane2;

	/*s2 = (t_sphere2*)malloc(sizeof(t_sphere2));*/
	hyper = (t_quad*)malloc(sizeof(t_quad));
	hyper->matt = (t_vec3d){1000, -190, 700};
	hyper->matr = (t_vec3d){0, 0, 0.2};
	hyper->mats = (t_vec3d){1, 1, 1};
	hyper->a = 0.0002;
	hyper->b = -0.0002;
	hyper->c = 0.0002;
	hyper->r = -1;
	hyper2 = (t_quad*)malloc(sizeof(t_quad));
	hyper2->matt = (t_vec3d){-100, -190, 700};
	hyper2->matr = (t_vec3d){0, 0, 0};
	hyper2->mats = (t_vec3d){1, 1, 1};
	hyper2->a = 0.00008;
	hyper2->b = 0.00002;
	hyper2->c = 0.00008;
	hyper2->r = -1;
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->matt = (t_vec3d){0, -700, 800};
	plane->matr = (t_vec3d){0, 0, 0};
	plane->mats = (t_vec3d){1, 1, 1};
	plane2 = (t_plane*)malloc(sizeof(t_plane));
	plane2->matt = (t_vec3d){-300, -700, 800};
	plane2->matr = (t_vec3d){0, 0, -1.5708};
	plane2->mats = (t_vec3d){1, 1, 1};
	/*s2->pos = (t_vec3d){0, 0, 0};*/
	/*s2->matt = (t_vec3d){1000, -190, 700};*/
	/*s2->matr = (t_vec3d){0, 0, 0};*/
	/*s2->mats = (t_vec3d){1, 1, 1};*/
	/*s2->radius = 1000;*/
	scene->obj = NULL;
	scene->light = NULL;
	vec_init(&scene->cam.pos, 350.f, 10.f, -2000.f);
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
	init_dotlight(&light, (t_vec3d){200.f, 50.f, 500.f}, (t_color){1.0f, 1.0f, 1.f});
	init_dotlight(&light2, (t_vec3d){440.f, 200.f, -1000.f}, (t_color){0.1f, 0.1f, 0.1f});
	mtl.color.r = 1.0f; mtl.color.g = 0.32f; mtl.color.b = 0.0f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.0f; mtl.reflect = 0;
	/*s2->mtl = mtl;*/
	hyper->mtl = mtl;
	hyper2->mtl = mtl;
	mtl.color.r = 0.7f; mtl.color.g = 1.f; mtl.color.b = 0.2f;
	mtl.specular.r = 0.1f; mtl.specular.g = 0.1f; mtl.specular.b = 0.1f; mtl.reflect = 0.3;
	plane->mtl = mtl;
	plane2->mtl = mtl;
	/*init_sphere(scene, 100, (t_vec3d){0.f, 170.f, 700.f}, mtl);*/
	mtl.color.r = 0.1f; mtl.color.g = 0.2f; mtl.color.b = 0.7f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.f; mtl.reflect = 0.3;
	/*init_sphere(scene, 100, (t_vec3d){400.f, 190.f, 500.f}, mtl);*/
	mtl.color.r = 0.7f; mtl.color.g = 1.f; mtl.color.b = 0.2f;
	mtl.specular.r = 0.1f; mtl.specular.g = 0.1f; mtl.specular.b = 0.1f; mtl.reflect = 0;
	/*init_plane(scene, (t_vec3d){0.f, 0.f, -1.f}, (t_vec3d){ 300, 200, 800}, mtl);*/
	/*init_plane(scene, (t_vec3d){1.f, 0.f, 0.f}, (t_vec3d){ -50.f, 200, 800}, mtl);*/
	/*init_plane(scene, (t_vec3d){0.f, 1.f, 0.f}, (t_vec3d){ 300, -700, 800}, mtl);*/
	mtl.color.r = 0.2f; mtl.color.g = 8.f; mtl.color.b = 0.4f;
	mtl.specular.r = 0.1f; mtl.specular.g = 0.1f; mtl.specular.b = 0.0f; mtl.reflect = 0.7;
	/*init_plane(scene, (t_vec3d){0.f, -1.f, 0.f}, (t_vec3d){ 300, 400, 800}, mtl);*/
	/*addobject(&scene->obj, s2, 'S');*/
	addobject(&scene->obj, hyper, 'h');
	addobject(&scene->obj, plane, 'P');
	addobject(&scene->obj, plane2, 'P');
	addobject(&scene->obj, hyper2, 'h');
	setobjfun(scene->obj);
	addolight(&scene->light,&light);
	addolight(&scene->light,&light2);
}

int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti)
{
	if (opti & UNDERSAMPLE)
	{
		rt(scene, buff->c, opti);
		buffer_us(buff);
		render(e, scene, buff->a);
	}
	else if (buff->aa == 1) {
		rt(scene, buff->b, opti);
		render(e, scene, buff->b);
	}
	else {
		rt(scene, buff->b, opti);
		buffer_ss(buff);
		render(e, scene, buff->a);
	}
	/*list_delall(&scene.obj, delete_object);*/
	/*list_delall(&scene.light, delete_light);*/
	return 0;
}
