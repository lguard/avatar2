/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:15:08 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:06:55 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec.h"
# include "list.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_ray
{
	t_vec3d	pos;
	t_vec3d	dir;
}				t_ray;

typedef struct	s_hit
{
	char	didit;
	t_flt	t;
	t_flt	reflect;
	t_vec3d	dir;
	t_vec3d	normal;
	t_vec3d	hitpoint;
	t_vec3d	raypos;
	t_mtl	*mtl;
	int		id;
}				t_hit;

/*
**	ray_transform.c
*/
void			ray_translate(t_ray *ray, t_flt tx, t_flt ty, t_flt tz);
void			ray_rotate(t_ray *ray, t_flt rx, t_flt ry, t_flt rz);
void			ray_scale(t_ray *ray, t_flt tx, t_flt ty, t_flt tz);
t_ray			ray_invertmat(t_ray *sr, t_vec3d *mt, t_vec3d *mr, t_vec3d *ms);

/*
**	ray.c
*/
void			hit_switch(t_flt *t, int id, t_hit *hit, t_ray *ray);
void			hit_clear(t_hit *hit);

#endif
