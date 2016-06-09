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

int main(void)
{
	t_env		e;
	t_scene	scene;
	t_ray	ray;
	t_sphere	s;
	t_sphere	s2;
	t_plane		p1;
	t_list	*objlst;
	t_list	*lightlst;
	t_hit	hit;
	t_dotlight	light;
	t_dotlight	light2;
	t_mtl		mtl;

	vec_init(&s.pos, 233.f, 290.f, 400.f);
	s.radius = 100;
	vec_init(&s2.pos, 424.f, 290.f, 500.f);
	s2.radius = 100;
	vec_init(&ray.dir, 0.f, 0.f, 1.f);
	scene.width = 640;
	scene.height = 480;
	init_dotlight(&light, (t_vec3d){0.f, 0.f, -100.f}, (t_vec3d){0.5f, 0.5f, 0.72});
	init_dotlight(&light2, (t_vec3d){100.f, 140.f, -1000.f}, (t_vec3d){0.4f, 0.6f, 0.0f});
	mtl.color.r = 7.0f; mtl.color.g = 0.32f; mtl.color.b = 0.0f;
	mtl.specular.r = 1.0f; mtl.specular.g = 0.32f; mtl.specular.b = 0.0f; mtl.reflect = 0.4;
	s.mtl = mtl;
	mtl.color.r = 0.1f; mtl.color.g = 0.2f; mtl.color.b = 0.7f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.f; mtl.reflect = 0.6;
	s2.mtl = mtl;
	s.id = 0;
	s2.id = 1;
	s2.mtl = mtl;
	mtl.color.r = 0.2f; mtl.color.g = 0.0f; mtl.color.b = 0.0f;
	mtl.specular.r = 0.5f; mtl.specular.g = 0.5f; mtl.specular.b = 0.5f; mtl.reflect = 0.7;
	p1.mtl = mtl;
	p1.id = 2;
	vec_init(&p1.normal, 0.f, 0.f, -1.f);
	vec_normalize(&p1.normal);
	vec_init(&p1.pos, 0.f, 0.f, 500.f);
	objlst = NULL;
	lightlst = NULL;
	addobject(&objlst, &s, 's');
	addobject(&objlst, &s2, 's');
	addobject(&objlst, &p1, 'p');
	setobjfun(objlst);
	list_pushfront(&lightlst, (void*)&light);
	list_pushfront(&lightlst, (void*)&light2);
	sdl_init(&e);
	SDL_SetRenderDrawColor(e.img, 0, 0, 0, 255);
	SDL_RenderClear(e.img);
	t_color	 **a = create_buffer(scene.width, scene.height);
	t_color	 **b = create_buffer(scene.width, scene.height);
	for (int x = 0 ; x < scene.width;++x) {
		for (int y = 0 ; y < scene.height;++y) {
			t_vec3d color = {0.f, 0.f, 0.f};
			t_vec3d color2 = {0.f, 0.f, 0.f};
			hit.t = 20000;
			hit.didit = 0;
			double	rc = 1.f;
			vec_init(&ray.dir, 0.f, 0.f, 1.f);
			vec_init(&ray.pos, x, y, -1000.0f);
			ray_trace(&ray, objlst, &hit);
			if (hit.didit)
			{
				t_list *ptr = lightlst;
				while (ptr)
				{
					dotlight(&color, (t_dotlight*)ptr->data, &hit, objlst);
					ptr = ptr->next;
				}
				color.x *= rc * (1 - hit.reflect);
				color.y *= rc * (1 - hit.reflect);
				color.z *= rc * (1 - hit.reflect);
				if (hit.id != 2)
				{
				rc *= hit.reflect;
				ray.dir = vec_reflect(&ray.dir, &hit.normal);
				ray.pos = hit.hitpoint;
				hit.didit = 0;
				ray_trace(&ray, objlst, &hit);
				if (hit.didit)
				{
					t_list *ptr2 = lightlst;
					while (ptr2)
					{
						dotlight(&color2, (t_dotlight*)ptr2->data, &hit, objlst);
						ptr2 = ptr2->next;
					}
					color2.x *= rc * (1 - hit.reflect);
					color2.y *= rc * (1 - hit.reflect);
					color2.z *= rc * (1 - hit.reflect);
					rc *= hit.reflect;
				}
				}
				a[x][y].r = color.x + color2.x;
				a[x][y].g = color.y + color2.y;
				a[x][y].b = color.z + color2.z;
				/*sdl_putpxl(&e, x, y, (unsigned char)(color.x*255.0f), (unsigned char)(color.y*255.0f), (unsigned char)(color.z*255.0f));*/
			}
		}
	}
	AA(a, b, scene.width, scene.height);
	for (int x = 0 ; x < scene.width;++x) {
		for (int y = 0 ; y < scene.height;++y) {
				sdl_putpxl(&e, x, scene.height - y, (unsigned char)(b[x][y].r*255.0f), (unsigned char)(b[x][y].g*255.0f), (unsigned char)(b[x][y].b*255.0f));
		}
	}
	/*int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);*/
	/*write_tga_header(fd, &scene, b);*/
	sdl_main_loop(&e);
	sdl_quit(&e);
	return 0;
}
