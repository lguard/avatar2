#ifndef OBJECT_H
# define OBJECT_H

# include <stdlib.h>

typedef struct	s_objfun
{
	char	type;
	char	*name;
}				t_objfun;


typedef struct	s_obj
{
	char	type;
	void	*object;
}				t_obj;

char	*getobjfun(t_obj *obj);

#endif
