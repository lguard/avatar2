/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:14:35 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:45:36 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	uint16_t	id;
	t_mtl		mtl;
	t_vec3d		matt;
	t_vec3d		matr;
	t_vec3d		mats;
	t_flt		a;
	t_flt		b;
	t_flt		c;
	t_flt		r;

}				t_quad;

/*
**	quad.c
*/
void			solve_quadratic(t_flt *t, t_flt a, t_flt b, t_flt c);
t_flt			dot_produce_elips(t_vec3d a, t_vec3d b, t_vec3d c);

/*
**	surface_hyperboloid.c
*/
void			surface_hyperboloid(t_ray *srcray, void *quad, t_hit *hit);
void			surface_hyperboloid_normal(void *hyperboloid, t_hit *hit);
t_quad			*surface_default_hyperboloid(t_vec3d *pos);

/*
**	surface_cone.c
*/
void			surface_cone(t_ray *srcray, void *quad, t_hit *hit);
void			surface_cone_normal(void *hyperboloid, t_hit *hit);
t_quad			*surface_default_cone(t_vec3d *pos);

/*
**	surface_cylindre.c
*/
void			surface_cylindre(t_ray *srcray, void *quad, t_hit *hit);
void			surface_cylindre_normal(void *hyperboloid, t_hit *hit);
t_quad			*surface_default_cylindre(t_vec3d *pos);

/*
**	surface_sphere.c
*/
void			surface_sphere(t_ray *srcray, void *quad, t_hit *hit);
void			surface_sphere_normal(void *quad, t_hit *hit);
t_quad			*surface_default_sphere(t_vec3d *pos);

#endif
