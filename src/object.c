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
		if (((t_obj*)(obj->data))->type == SPHERE)
		{
			((t_obj*)(obj->data))->hit = &surface_sphere;
			((t_obj*)(obj->data))->normal = &surface_sphere_normal;
		}
		if (((t_obj*)(obj->data))->type == CONE)
		{
			((t_obj*)(obj->data))->hit = &surface_cone;
			((t_obj*)(obj->data))->normal = &surface_cone_normal;
		}
		if (((t_obj*)(obj->data))->type == CYLINDRE)
		{
			((t_obj*)(obj->data))->hit = &surface_cylindre;
			((t_obj*)(obj->data))->normal = &surface_cylindre_normal;
		}
		if (((t_obj*)(obj->data))->type == PLANE)
		{
			((t_obj*)(obj->data))->hit = &surface_plane;
			((t_obj*)(obj->data))->normal = &surface_plane_normal;
		}
		if (((t_obj*)(obj->data))->type == HYBERBOLE)
		{
			((t_obj*)(obj->data))->hit = &surface_hyperboloid;
			((t_obj*)(obj->data))->normal = &surface_hyperboloid_normal;
		}
		else
			((t_obj*)(obj->data))->hit = &hit_error;
		obj = obj->next;
	}
}

void	setobjfun2(t_obj *obj)
{
	if (obj->type == SPHERE)
	{
		obj->hit = &surface_sphere;
		obj->normal = &surface_sphere_normal;
	}
	if (obj->type == CONE)
	{
		obj->hit = &surface_cone;
		obj->normal = &surface_cone_normal;
	}
	if (obj->type == CYLINDRE)
	{
		obj->hit = &surface_cylindre;
		obj->normal = &surface_cylindre_normal;
	}
	if (obj->type == PLANE)
	{
		obj->hit = &surface_plane;
		obj->normal = &surface_plane_normal;
	}
	if (obj->type == HYBERBOLE)
	{
		obj->hit = &surface_hyperboloid;
		obj->normal = &surface_hyperboloid_normal;
	}
	else
		obj->hit = &hit_error;
}

void	addobject(t_list **objlist, void *object, uint16_t type)
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
	return (NULL);
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
	return (((t_id*)obj)->id - *(uint16_t*)id);
}
