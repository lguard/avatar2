#ifndef MTL_H
# define MTL_H

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct	s_mtl
{
	t_color	color;
	t_color	specular;
	double	reflect;
	double	power;
}				t_mtl;

#endif /* MTL_H */
