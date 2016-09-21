#include "save.h"

void		value_to_file(int fd, void *v, int16_t size, int16_t type)
{
	write(fd, &type, (sizeof(int16_t)));
	write(fd, v, size);
}

void		load_light(int fd, t_scene *scene)
{
	t_dotlight	*light;

	light = (t_dotlight*)malloc(sizeof(t_dotlight));
	read(fd, light, sizeof(t_dotlight));
	vec_display(&light->pos);
	addolight(&scene->light, light);
}

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

void		load_cam(int fd, t_scene *scene)
{
	read(fd, &scene->cam, sizeof(t_cam));
}

int		select_surface(int fd, t_scene *scene, uint16_t type)
{
	if (type == 0)
		load_light(fd, scene);
	else if (type == 1)
		load_sphere(fd, scene);
	else if (type == 2)
		load_cone(fd, scene);
	else if (type == 3)
		load_cylindre(fd, scene);
	else if (type == 4)
		load_hyperbol(fd, scene);
	else if (type == 5)
		load_plane(fd, scene);
	else if (type == 6)
		load_cam(fd, scene);
	else
		return (1);
	return (0);
}

void		read_scene(const char *pathname, t_scene *scene)
{
	int		fd;
	int16_t	type;

	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		return ;
	list_delall(&scene->obj, &delete_object);
	list_delall(&scene->light, &light_free);
	while (42)
	{
		if (read(fd, &type, sizeof(int16_t)) <= 0)
			break ;
		if (select_surface(fd, scene, type))
			break ;
	}
	close(fd);
}

void		write_s(const char *pathname, t_scene *e)
{
	int		fd;
	t_list	*ptr;

	fd = open(pathname, O_CREAT | O_WRONLY, S_IROTH | S_IRWXU);
	if (fd < 0)
		return ;
	ptr = e->light;
	while (ptr)
	{
		vec_display(&((t_dotlight*)ptr->data)->pos);
		value_to_file(fd, (void*)(ptr->data), sizeof(t_dotlight), 0);
		ptr = ptr->next;
	}
	ptr = e->obj;
	while (ptr)
	{
		if (((t_obj*)(ptr->data))->type == 5)
			value_to_file(fd, ((t_obj*)ptr->data)->object, sizeof(t_plane),
			((t_obj*)(ptr->data))->type);
		else
			value_to_file(fd, ((t_obj*)ptr->data)->object, sizeof(t_quad),
			((t_obj*)(ptr->data))->type);
		ptr = ptr->next;
	}
	value_to_file(fd, &e->cam, sizeof(t_cam), 6);
}
