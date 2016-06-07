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
	t_list	*objlst;
	t_list	*lightlst;
	t_hit	hit;
	t_dotlight	light;
	t_dotlight	light2;
	t_mtl		mtl;

	vec_init(&s.pos, 430.f, 200.f, -300.f);
	s.radius = 30;
	vec_init(&s2.pos, 320.f, 240.f, 200.f);
	s2.radius = 130;
	vec_init(&ray.dir, 0.f, 0.f, 1.f);
	scene.width = 640;
	scene.height = 480;
	init_dotlight(&light, (t_vec3d){600.f, 0.f, -2000.f}, (t_vec3d){1.f, 1.f, 1.f});
	init_dotlight(&light2, (t_vec3d){100.f, 240.f, -1070.f}, (t_vec3d){1.0f, 1.0f, 1.0f});
	mtl.color.r = 7.0f; mtl.color.g = 0.32f; mtl.color.b = 0.0f;
	mtl.specular.r = 1.0f; mtl.specular.g = 0.32f; mtl.specular.b = 0.0f;
	s.mtl = mtl;
	mtl.color.r = 0.1f; mtl.color.g = 0.2f; mtl.color.b = 0.7f;
	mtl.specular.r = 1.0f; mtl.specular.g = 1.f; mtl.specular.b = 1.f;
	s2.mtl = mtl;
	s.id = 0;
	s2.id = 1;
	objlst = NULL;
	lightlst = NULL;
	addobject(&objlst, &s, 's');
	addobject(&objlst, &s2, 's');
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
			hit.t = 20000;
			hit.didit = 0;
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
				a[x][y].r = color.x;
				a[x][y].g = color.y;
				a[x][y].b = color.z;
				/*sdl_putpxl(&e, x, y, (unsigned char)(color.x*255.0f), (unsigned char)(color.y*255.0f), (unsigned char)(color.z*255.0f));*/
			}
		}
	}
	AA(a, b, scene.width, scene.height);
	for (int x = 0 ; x < scene.width;++x) {
		for (int y = 0 ; y < scene.height;++y) {
				sdl_putpxl(&e, x, y, (unsigned char)(b[x][y].r*255.0f), (unsigned char)(b[x][y].g*255.0f), (unsigned char)(b[x][y].b*255.0f));
		}
	}
	int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);
	write_tga_header(fd, &scene, b);
	sdl_main_loop(&e);
	sdl_quit(&e);
	return 0;
}
