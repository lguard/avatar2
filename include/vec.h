#ifndef VEC_H
# define VEC_H

# include <math.h>
# include <stdio.h>
# include "rt.h"

# define CUBE(x) x*x

typedef struct	s_vec3d
{
	FLOAT	x;
	FLOAT	y;
	FLOAT	z;
}				t_vec3d;

t_vec3d		vec_add(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_sub(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_mul(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_scale(const t_vec3d*, const FLOAT);
t_vec3d		vec_reflect(const t_vec3d*, const t_vec3d*);
t_vec3d		vec_rotaion_x(t_vec3d *a, FLOAT angle);
t_vec3d		vec_rotaion_y(t_vec3d *a, FLOAT angle);
t_vec3d		vec_rotaion_z(t_vec3d *a, FLOAT angle);
FLOAT		vec_getsquare_length(const t_vec3d *a);
FLOAT		vec_dotproduct(const t_vec3d*, const t_vec3d*);
void		vec_init(t_vec3d*, FLOAT, FLOAT, FLOAT);
void		vec_display(t_vec3d*);
void		vec_normalize(t_vec3d*);
void		vec_translate(t_vec3d*vec, FLOAT tx, FLOAT ty, FLOAT tz);
void		vec_rotate(t_vec3d*vec, FLOAT rx, FLOAT ry, FLOAT rz);
void		vec_matscale(t_vec3d*vec, FLOAT tx, FLOAT ty, FLOAT tz);

#endif
