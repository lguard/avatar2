#include "object.h"
#include "stdio.h"

uint16_t	get_id(void)
{
	static uint16_t i = 0;
	return (i++);
}

void	hit_error(t_ray *ray, void *non, t_hit *hit)
{
	(void)ray;
	(void)non;
	(void)hit;
	printf("Error: can't select object function %s\n", __FILE__);
}

void	setobjfun(t_list *obj)
{
	while (obj)
	{
		switch (((t_obj*)(obj->data))->type)
		{
			case 's':
				((t_obj*)(obj->data))->hit = &hit_sphere;
				break ;
			case 'S':
				((t_obj*)(obj->data))->hit = &hit_sphere2;
				break ;
			case 'p':
				((t_obj*)(obj->data))->hit = &hit_plane;
				break ;
			case 'P':
				((t_obj*)(obj->data))->hit = &surface_plane;
				((t_obj*)(obj->data))->normal = &surface_plane_normal;
				break ;
			case 'h':
				((t_obj*)(obj->data))->hit = &surface_hyperboloid;
				((t_obj*)(obj->data))->normal = &surface_hyperboloid_normal;
				break ;
			default :
				((t_obj*)(obj->data))->hit = &hit_error;
				break ;
		}
		obj = obj->next;
	}
}

void	addobject(t_list **objlist, void *object, char type)
{
	t_obj			*new;
	t_obj_header	*h;

	new = (t_obj*)malloc(sizeof(t_obj));
	new->type = type;
	new->object = object;
	new->id = get_id();
	h = (t_obj_header*)object;
	h->id = new->id;
	list_pushfront(objlist, (void*)new);
}

t_obj	*getobject_by_id(int id, t_list *objlist)
{
	t_obj_header	*idobj;

	while (objlist)
	{
		idobj = (t_obj_header*)(((t_obj*)objlist->data)->object);
		if (idobj->id == id)
			return (objlist->data);
		objlist = objlist->next;
	}
	return NULL;
}

void	delete_object(void *obj)
{
	(void)obj;
	free(obj);
}
