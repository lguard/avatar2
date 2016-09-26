/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:24:35 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:25:03 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vec.h"
# include "ray.h"
# include "math.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_sphere
{
	int		id;
	t_mtl	mtl;
	t_vec3d	pos;
	t_flt	radius;
}				t_sphere;

typedef struct	s_sphere2
{
	int		id;
	t_mtl	mtl;
	t_vec3d	matt;
	t_vec3d	matr;
	t_vec3d	mats;
	t_vec3d	pos;
	t_flt	radius;
}				t_sphere2;

void			hit_sphere(t_ray *ray, void *sphere, t_hit *hit);
t_vec3d			hit_normal(t_ray *ray, t_sphere *s, t_hit *hit);
t_vec3d			hit_normal2(t_ray *ray, t_sphere2 *s, t_hit *hit);
void			hit_sphere2(t_ray *srcray, void *sphere, t_hit *hit);

#endif
