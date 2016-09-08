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
	char		type;
	void		*object;
	void		(*hit)(t_ray *, void *, t_hit *);
	void		(*normal)(void *, t_hit *);
}				t_obj;

void		setobjfun(t_list *obj);
void		hit_error(t_ray *ray, void *non, t_hit *hit);
void		addobject(t_list **objlist, void *object, char type);
void		delete_object(void *obj);
t_obj		*getobject_by_id(int id, t_list *objlist);
uint16_t	get_id(void);
int			remove_obj(void *obj, void *id);

#endif
