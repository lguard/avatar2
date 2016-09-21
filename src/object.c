#include "object.h"

void	setobjfun(t_obj *obj)
{
	if (obj->type == SPHERE)
	{
		obj->hit = &surface_sphere;
		obj->normal = &surface_sphere_normal;
	}
	else if (obj->type == CONE)
	{
		obj->hit = &surface_cone;
		obj->normal = &surface_cone_normal;
	}
	else if (obj->type == CYLINDRE)
	{
		obj->hit = &surface_cylindre;
		obj->normal = &surface_cylindre_normal;
	}
	else if (obj->type == PLANE)
	{
		obj->hit = &surface_plane;
		obj->normal = &surface_plane_normal;
	}
	else if (obj->type == HYBERBOLE)
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
	setobjfun(new);
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
