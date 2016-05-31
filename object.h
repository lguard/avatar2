#ifndef OBJECT_H
# define OBJECT_H

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

#endif
