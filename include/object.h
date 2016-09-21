#ifndef OBJECT_H
# define OBJECT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "sphere.h"
# include "plane.h"
# include "quad.h"
# include "ray.h"
# include "list.h"
# include "rt.h"

# define SPHERE 1
# define CONE 2
# define CYLINDRE 3
# define HYBERBOLE 4
# define PLANE 5

typedef struct	s_obj_header
{
	uint16_t	id;
	t_mtl		mtl;
	t_vec3d		matt;
	t_vec3d		matr;
	t_vec3d		mats;
}				t_obj_header;

typedef struct	s_id
{
	uint16_t	id;
}				t_id;

typedef struct	s_obj
{
	uint16_t	id;
	uint16_t	type;
	void		*object;
	void		(*hit)(t_ray *, void *, t_hit *);
	void		(*normal)(void *, t_hit *);
}				t_obj;

/*
**	object_error.c
*/
void	hit_error(t_ray *ray, void *non, t_hit *hit);

/*
**	object.c
*/
void	setobjfun(t_obj *obj);
void	addobject(t_list **objlist, void *object, uint16_t type);
void	delete_object(void *obj);
t_obj	*getobject_by_id(int id, t_list *objlist);
int		remove_obj(void *obj, void *id);

#endif
