#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
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

/*[>int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);<]*/
/*[>write_tga_header(fd, &scene, b);<]*/

void		light_and_reflect(t_ray *ray, t_hit *hit, t_scene *scene, t_color *colora)
{
	t_color colorb;
	t_list	*ptr;
	FLOAT	rc;

	color_init(colora, 0, 0, 0);
	rc = 1.f;
	int i = 0;
	while(42)
	{
		color_init(&colorb, 0, 0, 0);
		ray_trace(ray, scene->obj, hit);
		if (!hit->didit)
			return ;
		ptr = scene->light;
		while (ptr)
		{
			dotlight(&colorb, (t_dotlight*)ptr->data, hit, scene->obj);
			ptr = ptr->next;
		}
		/*if (i != 0)*/
			color_scale(&colorb, (rc * (1- hit->reflect)));
		rc *= hit->reflect;
		ray->dir = vec_reflect(&ray->dir, &hit->normal);
		ray->pos = hit->hitpoint;
		hit->didit = 0;
		color_add(colora, &colorb);
		++i;
		if (i >= 2)
			return ;
	}
}

void	rt(t_scene *scene, t_color **a)
{
	t_hit hit;
	t_ray ray;
	FLOAT xindent;
	FLOAT yindent;

	xyratio(&xindent, &yindent, &scene->cam, scene->width, scene->height);
	for (int x = 0 ; x < scene->width;++x) {
		for (int y = 0 ; y < scene->height;++y) {
			t_vec3d planepix = getplanepix(&scene->cam, x, y, xindent, yindent);
			hit.t = 20000;
			hit.didit = 0;
			vec_normalize(&planepix);
			vec_init(&ray.dir, planepix.x, planepix.y, planepix.z);
			vec_init(&ray.pos, scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
			light_and_reflect(&ray, &hit, scene, &a[x][y]);
		}
	}
}

void	single_rt(t_scene *scene, int x, int y)
{
	t_hit hit;
	t_ray ray;
	FLOAT xindent;
	FLOAT yindent;
	t_color color;

	xyratio(&xindent, &yindent, &scene->cam, scene->width, scene->height);
	t_vec3d planepix = getplanepix(&scene->cam, x, y, xindent, yindent);
	hit.t = 20000;
	hit.didit = 0;
	vec_normalize(&planepix);
	vec_init(&ray.dir, planepix.x, planepix.y, planepix.z);
	vec_init(&ray.pos, scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);

	light_and_reflect(&ray, &hit, scene, &color);
	printf("\033[38;2mr %d, g %d, b %d\n", (unsigned char)(color.r*255.0f), (unsigned char)(color.g*255.0f), (unsigned char)(color.b*255.0f));
}

void	render(t_env *e, t_scene *scene, t_color **a)
{
	for (int x = 0 ; x < scene->render_width;++x) {
		for (int y = 0 ; y < scene->render_height;++y) {
				sdl_putpxl(e, x, y, (unsigned char)( a[x][y].r*255.0f), (unsigned char)( a[x][y].g*255.0f), (unsigned char)( a[x][y].b*255.0f));
		}
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
	printf("add - %p\n", s);
	++i;
}

int mainrt(t_env *e)
{
	t_scene	scene;
	t_sphere	s;
	t_sphere	s2;
	t_plane		p1;
	t_plane		p2;
	t_plane		p3;
	t_plane		p4;
	t_dotlight	light;
	t_dotlight	light2;
	t_mtl		mtl;

	scene.obj = NULL;
	scene.light = NULL;
	vec_init(&scene.cam.pos, 250.f, 10.f, -2000.f);
	vec_init(&scene.cam.dirvec, 0.f, 0.f, 1.f);
	vec_init(&scene.cam.upvec, 0.f, 1.f, 0.f);
	scene.cam.wfov = 1.0;
	scene.cam.hfov = 1.0;
	scene.cam.rightvec = vec_mul(&scene.cam.dirvec, &scene.cam.upvec);
	scene.cam.viewplane_upleft = getupleft(&scene.cam, scene.cam.wfov, scene.cam.hfov);
	scene.cam.distance = 1.f;
	vec_init(&s.pos, 0.f, 170.f, 700.f);
	s.radius = 100;
	vec_init(&s2.pos, 400.f, 190.f, 500.f);
	s2.radius = 100;
	init_dotlight(&light, (t_vec3d){100.f, 50.f, 600.f}, (t_color){1.0f, 1.0f, 1.f});
	init_dotlight(&light2, (t_vec3d){440.f, 200.f, -1000.f}, (t_color){0.1f, 0.1f, 0.1f});
	mtl.color.r = 1.0f; mtl.color.g = 0.32f; mtl.color.b = 0.0f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.0f; mtl.reflect = 0;
	s.mtl = mtl;
	mtl.color.r = 0.1f; mtl.color.g = 0.2f; mtl.color.b = 0.7f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.f; mtl.reflect = 0.3;
	s2.mtl = mtl;
	s.id = 0;
	s2.id = 1;
	s2.mtl = mtl;
	init_sphere(&scene, 100, (t_vec3d){400.f, 190.f, 500.f}, mtl);
	mtl.color.r = 0.7f; mtl.color.g = 1.f; mtl.color.b = 0.2f;
	mtl.specular.r = 0.1f; mtl.specular.g = 0.1f; mtl.specular.b = 0.1f; mtl.reflect = 0;
	p1.mtl = mtl;
	p3.mtl = mtl;
	p4.mtl = mtl;
	mtl.color.r = 0.2f; mtl.color.g = 8.f; mtl.color.b = 0.4f;
	mtl.specular.r = 0.1f; mtl.specular.g = 0.1f; mtl.specular.b = 0.0f; mtl.reflect = 0.7;
	p2.mtl = mtl;
	p1.id = 2;
	p2.id = 3;
	p3.id = 4;
	p4.id = 4;
	vec_init(&p1.normal, 0.f, 0.f, -1.f);
	vec_normalize(&p1.normal);
	vec_init(&p1.pos, 300.f, 200.f, 800.f);
	vec_init(&p2.normal, 0.f, -1.f, -0.6f);
	vec_normalize(&p2.normal);
	vec_init(&p2.pos, 300.f, 100.f, 800.f);
	vec_init(&p3.normal, 1.f, 0.f, 0.f);
	vec_normalize(&p3.normal);
	vec_init(&p3.pos, -50.f, 200.f, 800.f);
	vec_init(&p4.normal, 0.f, 1.f, 0.f);
	vec_normalize(&p4.normal);
	vec_init(&p4.pos, 300.f, -600.f, 800.f);
	addobject(&scene.obj, &s, 's');
	/*addobject(&scene.obj, &s2, 's');*/
	addobject(&scene.obj, &p1, 'p');
	addobject(&scene.obj, &p2, 'p');
	addobject(&scene.obj, &p3, 'p');
	addobject(&scene.obj, &p4, 'p');
	setobjfun(scene.obj);
	addolight(&scene.light,&light);
	addolight(&scene.light,&light2);
	int aa = 128;
	scene.render_width = 1000;
	scene.render_height = 1000;
	scene.width = scene.render_width*aa;
	scene.height = scene.render_height *aa;
	t_buffer buff;
	buffer_init(&buff);
	buffer_reload(&buff, scene.render_width, scene.render_height, aa);
	struct timeval time;
	if(gettimeofday( &time, 0 ))
		return -1;
	long cur_time = 1000000 * time.tv_sec + time.tv_usec;
	double sec1 = cur_time / 1000000.0;
	rt(&scene, buff.b);
	if (aa == 1) {
		render(e, &scene, buff.b);
	}
	else {
		buffer_ss(&buff);
		render(e, &scene, buff.a);
	}
	if(gettimeofday( &time, 0 ))
		return -1;
	cur_time = 1000000 * time.tv_sec + time.tv_usec;
	double sec2 = cur_time / 1000000.0;
	printf("%f\n", sec2-sec1);
	list_delall(&scene.obj, delete_object);
	list_delall(&scene.light, delete_light);
	/*int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);*/
	/*write_tga_header(fd, &scene, buff.a);*/
	/*close(fd);*/
	return 0;
}
