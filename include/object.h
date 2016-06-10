#ifndef OBJECT_H
# define OBJECT_H

# include <stdlib.h>
# include <unistd.h>
# include "sphere.h"
# include "plane.h"
# include "ray.h"
# include "list.h"

typedef struct	s_obj
{
	char	type;
	void	*object;
	void	(*hit)(t_ray *, void *, t_hit *);
}				t_obj;

void	setobjfun(t_list *obj);
void	hit_error(t_ray *ray, void *non, t_hit *hit);
void	addobject(t_list **objlist, void *object, char type);
void	delete_object(void *obj);

#endif
