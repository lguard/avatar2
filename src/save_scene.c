#include "save.h"

void		value_to_file(int fd, void *v, int16_t size, int16_t type)
{
	write(fd, &type, (sizeof(int16_t)));
	write(fd, v, size);
}

/*void		read_scene(t_scene *scene, const char *pathname)*/
/*{*/
	/*int	fd;*/
	/*int16_t	type;*/

	/*fd = open(pathname, O_RDONLY);*/
	/*if (fd < 0)*/
		/*return ;*/
	/*while(42)*/
	/*{*/
		/*if (read(fd, &type, sizeof(int16_t)) <= 0)*/
			/*break;*/
		/*if (type == 0)*/
		/*{*/
			/*read(fd, &a, sizeof(t_lol));*/
		/*}*/
		/*else*/
		/*{*/
			/*read(fd, &b, sizeof(t_lol2));*/
		/*}*/
	/*}*/
	/*close(fd);*/
/*}*/

void		write_s(const char *pathname, t_scene *e)
{
	int	fd;
	t_list	*ptr;

	fd = open(pathname, O_CREAT | O_WRONLY, S_IROTH | S_IRWXU);
	if (fd < 0)
		return ;
	ptr = e->light;
	while (ptr)
	{
		value_to_file(fd, (void*)(ptr->data), sizeof(t_dotlight), 0);
		ptr = ptr->next;
	}
	ptr = e->obj;
	while (ptr)
	{
		if (((t_obj*)(ptr->data))->type == 6)
			value_to_file(fd, ptr->data, sizeof(t_plane), ((t_obj*)(ptr->data))->type);
		else
			value_to_file(fd, ptr->data, sizeof(t_quad), ((t_obj*)(ptr->data))->type);
		ptr = ptr->next;
	}
}
