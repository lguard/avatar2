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
	int width = scene->width ;
	int height = scene->height ;
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

	for (int x = 0 ; x < width;++x) {
		for (int y = 0 ; y < height;++y) {
				write_byte((unsigned char)(src[x][y].r*255.0f),fd);
				write_byte((unsigned char)(src[x][y].g*255.0f),fd);
				write_byte((unsigned char)(src[x][y].b*255.0f),fd);
		}
	}
}

/*[>int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);<]*/
/*[>write_tga_header(fd, &scene, b);<]*/

void		light_and_reflect(t_ray ray, t_hit hit, t_scene *scene, t_color *colora)
{
	t_color colorb;
	t_list	*ptr;
	double	rc;

	color_init(colora, 0, 0, 0);
	rc = 1.f;
	while(42)
	{
		color_init(&colorb, 0, 0, 0);
		ray_trace(&ray, scene->obj, &hit);
		if (!hit.didit)
			break ;
		ptr = scene->light;
		while (ptr)
		{
			dotlight(&colorb, (t_dotlight*)ptr->data, &hit, scene->obj);
			ptr = ptr->next;
		}
		color_scale(&colorb, (rc * (1- hit.reflect)));
		rc *= hit.reflect;
		ray.dir = vec_reflect(&ray.dir, &hit.normal);
		ray.pos = hit.hitpoint;
		hit.didit = 0;
		color_add(colora, &colorb);
	}
}

void	rt(t_scene *scene, t_color **a)
{
	t_hit hit;
	t_ray ray;
	double xindent;
	double yindent;

	xyratio(&xindent, &yindent, &scene->cam, scene->width, scene->height);
	for (int x = 0 ; x < scene->width;++x) {
		for (int y = 0 ; y < scene->height;++y) {
			t_vec3d planepix = getplanepix(&scene->cam, x, y, xindent, yindent);
			hit.t = 20000;
			hit.didit = 0;
			vec_normalize(&planepix);
			vec_init(&ray.dir, planepix.x, planepix.y, planepix.z);
			vec_init(&ray.pos, scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
			light_and_reflect(ray, hit, scene, &a[x][y]);
		}
	}
}

void	render(t_env *e, t_scene *scene, t_color **a)
{
	for (int x = 0 ; x < scene->render_width;++x) {
		for (int y = 0 ; y < scene->render_height;++y) {
				sdl_putpxl(e, x, (scene->render_height) - y, (unsigned char)( a[x][y].r*255.0f), (unsigned char)( a[x][y].g*255.0f), (unsigned char)( a[x][y].b*255.0f));
		}
	}
}

int main(void)
{
	/*t_env		e;*/
	t_scene	scene;
	t_ray	ray;
	t_sphere	s;
	t_sphere	s2;
	t_plane		p1;
	t_dotlight	light;
	t_dotlight	light2;
	t_mtl		mtl;

	vec_init(&scene.cam.pos, 200.f, 200.f, -1000.f);
	vec_init(&scene.cam.dirvec, 0.f, 0.f, 1.f);
	vec_init(&scene.cam.upvec, 0.f, 1.f, 0.f);
	scene.cam.rightvec = vec_mul(&scene.cam.dirvec, &scene.cam.upvec);
	scene.cam.viewplane_upleft = getupleft(&scene.cam);
	scene.cam.wfov = 0.5;
	scene.cam.hfov = 0.375;
	scene.cam.distance = 1.f;
	vec_init(&s.pos, 233.f, 290.f, 400.f);
	s.radius = 100;
	vec_init(&s2.pos, 424.f, 290.f, 400.f);
	s2.radius = 100;
	vec_init(&ray.dir, 0.f, 0.f, 1.f);
	init_dotlight(&light, (t_vec3d){0.f, 0.f, -100.f}, (t_color){0.5f, 0.5f, 0.72});
	init_dotlight(&light2, (t_vec3d){100.f, 140.f, -1000.f}, (t_color){1.0f, 1.0f, 1.0f});
	mtl.color.r = 7.0f; mtl.color.g = 0.32f; mtl.color.b = 0.0f;
	mtl.specular.r = 1.0f; mtl.specular.g = 0.32f; mtl.specular.b = 0.0f; mtl.reflect = 0.4;
	s.mtl = mtl;
	mtl.color.r = 0.1f; mtl.color.g = 0.2f; mtl.color.b = 0.7f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.f; mtl.reflect = 0.6;
	s2.mtl = mtl;
	s.id = 0;
	s2.id = 1;
	s2.mtl = mtl;
	mtl.color.r = 0.5f; mtl.color.g = 0.5f; mtl.color.b = 0.5f;
	mtl.specular.r = 0.5f; mtl.specular.g = 0.5f; mtl.specular.b = 0.5f; mtl.reflect = 1;
	p1.mtl = mtl;
	p1.id = 2;
	vec_init(&p1.normal, 1.f, 0.f, -1.f);
	vec_normalize(&p1.normal);
	vec_init(&p1.pos, 300.f, 200.f, 800.f);
	scene.obj = NULL;
	scene.light = NULL;
	addobject(&scene.obj, &s, 's');
	addobject(&scene.obj, &s2, 's');
	addobject(&scene.obj, &p1, 'p');
	setobjfun(scene.obj);
	list_pushfront(&scene.light, (void*)&light);
	list_pushfront(&scene.light, (void*)&light2);
	/*sdl_init(&e);*/
	/*SDL_SetRenderDrawColor(e.img, 0, 0, 0, 255);*/
	/*SDL_RenderClear(e.img);*/
	int aa = 1;
	scene.render_width = 640;
	scene.render_height = 480;
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
		/*render(&e, &scene, buff.b);*/
	}
	else {
		buffer_ss(&buff);
		/*render(&e, &scene, buff.a);*/
	}
	if(gettimeofday( &time, 0 ))
		return -1;
	cur_time = 1000000 * time.tv_sec + time.tv_usec;
	double sec2 = cur_time / 1000000.0;
	printf("%f\n", sec2-sec1);
	/*sdl_main_loop(&e);*/
	/*sdl_quit(&e);*/
	list_delall(&scene.obj, delete_object);
	list_delall(&scene.light, delete_light);
	return 0;
}
