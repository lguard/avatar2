#include "object.h"
#include "stdio.h"

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
			default :
				((t_obj*)(obj->data))->hit = &hit_error;
				break ;
		}
		obj = obj->next;
	}
}

void	addobject(t_list **objlist, void *object, char type)
{
	t_obj	*new;

	new = (t_obj*)malloc(sizeof(t_obj));
	new->type = type;
	new->object = object;
	list_pushfront(objlist, (void*)new);
}

t_obj	*getobject_by_id(int id, t_list **objlist)
{
	t_list		*new;
	t_id_obj	*idobj;

	new = *objlist;
	while (new)
	{
		idobj = (t_id_obj*)(((t_obj*)new->data)->object);
		if (idobj->id == id)
			return (new->data);
		new = new->next;
	}
	return NULL;
}

void	delete_object(void *obj)
{
	(void)obj;
	free(obj);
}
