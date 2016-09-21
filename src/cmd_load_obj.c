#include "save.h"

void		load_sphere(int fd, t_scene *scene)
{
	t_quad	*quad;

	quad = (t_quad*)malloc(sizeof(t_quad));
	read(fd, quad, sizeof(t_quad));
	addobject(&scene->obj, quad, 1);
}

void		load_cone(int fd, t_scene *scene)
{
	t_quad	*quad;

	quad = (t_quad*)malloc(sizeof(t_quad));
	read(fd, quad, sizeof(t_quad));
	addobject(&scene->obj, quad, 2);
}

void		load_cylindre(int fd, t_scene *scene)
{
	t_quad	*quad;

	quad = (t_quad*)malloc(sizeof(t_quad));
	read(fd, quad, sizeof(t_quad));
	addobject(&scene->obj, quad, 3);
}

void		load_hyperbol(int fd, t_scene *scene)
{
	t_quad	*quad;

	quad = (t_quad*)malloc(sizeof(t_quad));
	read(fd, quad, sizeof(t_quad));
	addobject(&scene->obj, quad, 4);
}

void		load_plane(int fd, t_scene *scene)
{
	t_plane	*plane;

	plane = (t_plane*)malloc(sizeof(t_plane));
	read(fd, plane, sizeof(t_plane));
	addobject(&scene->obj, plane, 5);
}
