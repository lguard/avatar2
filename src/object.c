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
				((t_obj*)(obj->data))->hit = &surface_sphere;
				((t_obj*)(obj->data))->normal = &surface_sphere_normal;
				break ;
			case 'c':
				((t_obj*)(obj->data))->hit = &surface_cone;
				((t_obj*)(obj->data))->normal = &surface_cone_normal;
				break ;
			case 'C':
				((t_obj*)(obj->data))->hit = &surface_cylindre;
				((t_obj*)(obj->data))->normal = &surface_cylindre_normal;
				break ;
			case 'p':
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

void	setobjfun2(t_obj *obj)
{
	switch (obj->type)
	{
		case 's':
			obj->hit = &hit_sphere;
			break ;
		case 'S':
			obj->hit = &surface_sphere;
			obj->normal = &surface_sphere_normal;
			break ;
		case 'c':
			obj->hit = &surface_cone;
			obj->normal = &surface_cone_normal;
			break ;
		case 'C':
			obj->hit = &surface_cylindre;
			obj->normal = &surface_cylindre_normal;
			break ;
		case 'p':
			obj->hit = &surface_plane;
			obj->normal = &surface_plane_normal;
			break ;
		case 'h':
			obj->hit = &surface_hyperboloid;
			obj->normal = &surface_hyperboloid_normal;
			break ;
		default :
			obj->hit = &hit_error;
			break ;
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
	setobjfun2(new);
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
	t_obj	*object;

	object = (t_obj*)obj;
	free(object->object);
	free(obj);
}

int		remove_obj(void *obj, void *id)
{
	printf("%u, %u\n", ((t_id*)obj)->id, *(uint16_t*)id);
	return (((t_id*)obj)->id - *(uint16_t*)id);
}
