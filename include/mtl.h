#ifndef MTL_H
# define MTL_H

#include "color.h"

typedef struct	s_mtl
{
	t_color	color;
	t_color	specular;
	double	reflect;
	double	power;
}				t_mtl;

#endif /* MTL_H */
