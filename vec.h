#ifndef VEC_H
# define VEC_H
#include <math.h>
#include <stdio.h>

typedef struct	s_vec3d
{
	double	x;
	double	y;
	double	z;
}				t_vec3d;

t_vec3d		vec_add(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_sub(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_mul(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_scale(const t_vec3d*, const double);
t_vec3d		vec_reflect(const t_vec3d*, const t_vec3d*);
double		vec_dotproduct(const t_vec3d*, const t_vec3d*);
void		vec_init(t_vec3d*, double, double, double);
void		vec_display(t_vec3d*);
void		vec_normalize(t_vec3d*);

#endif
