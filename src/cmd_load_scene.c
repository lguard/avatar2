#include "cmd.h"

void		load_light(int fd, t_scene *scene)
{
	t_dotlight	*light;

	light = (t_dotlight*)malloc(sizeof(t_dotlight));
	read(fd, light, sizeof(t_dotlight));
	addolight(&scene->light, light);
}

void		load_cam(int fd, t_scene *scene)
{
	read(fd, &scene->cam, sizeof(t_cam));
}
