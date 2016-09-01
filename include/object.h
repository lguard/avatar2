#ifndef OBJECT_H
# define OBJECT_H

# include <stdlib.h>
# include <unistd.h>
# include "sphere.h"
# include "plane.h"
# include "ray.h"
# include "list.h"
# include "rt.h"

typedef struct	s_id_obj
{
	int		id;
}				t_id_obj;

typedef struct	s_obj
{
	char	type;
	void	*object;
	void	(*hit)(t_ray *, void *, t_hit *);
}				t_obj;

void	setobjfun(t_list *obj);
void	hit_error(t_ray *ray, void *non, t_hit *hit);
void	addobject(t_list **objlist, void *object, char type);
t_obj	*getobject_by_id(int id, t_list **objlist);
void	delete_object(void *obj);

#endif
