#ifndef MTL_H
# define MTL_H

#include "color.h"
# include "rt.h"

typedef struct	s_mtl
{
	t_color	color;
	t_color	specular;
	FLOAT	reflect;
	FLOAT	power;
}				t_mtl;

#endif /* MTL_H */
