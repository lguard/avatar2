#ifndef QUAD_H
# define QUAD_H

# include <stdint.h>
# include "vec.h"
# include "ray.h"
# include "math.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_quad
{
	uint16_t		id;
	t_mtl			mtl;
	t_vec3d			matt;
	t_vec3d			matr;
	t_vec3d			mats;
	FLOAT			a;
	FLOAT			b;
	FLOAT			c;
	FLOAT			r;

}				t_quad;


void		solve_quadraticv2(FLOAT *t0, FLOAT *t1, FLOAT a, FLOAT b, FLOAT c);
FLOAT		dot_produce_elips(t_vec3d a, t_vec3d b, t_vec3d c);
void		surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit);
void		surface_hyperboloid_normal(void *hyperboloid, t_hit *hit);
t_quad		*surface_default_hyperboloid(t_vec3d *pos);

void		surface_cone(t_ray *srcray, void *quad, t_hit *hit);
void		surface_cone_normal(void *hyperboloid, t_hit *hit);
t_quad		*surface_default_cone(t_vec3d *pos);

void		surface_cylindre(t_ray *srcray, void *quad, t_hit *hit);
void		surface_cylindre_normal(void *hyperboloid, t_hit *hit);
t_quad		*surface_default_cylindre(t_vec3d *pos);

void		surface_sphere(t_ray *srcray, void *quad, t_hit *hit);
void		surface_sphere_normal(void *quad, t_hit *hit);
t_quad		*surface_default_sphere(t_vec3d *pos);

#endif /* QUAD_H */
