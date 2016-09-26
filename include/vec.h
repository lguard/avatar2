/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:25:34 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:27:23 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <math.h>
# include <stdio.h>
# include "rt.h"
# include "libft.h"

# define CUBE(x) x*x

typedef struct	s_vec3d
{
	t_flt	x;
	t_flt	y;
	t_flt	z;
}				t_vec3d;

t_vec3d			vec_add(const t_vec3d *a, const t_vec3d *b);
t_vec3d			vec_sub(const t_vec3d *a, const t_vec3d *b);
t_vec3d			vec_mul(const t_vec3d *a, const t_vec3d *b);
t_vec3d			vec_scale(const t_vec3d *a, const t_flt b);
t_vec3d			vec_reflect(const t_vec3d *a, const t_vec3d *b);
t_vec3d			vec_rotaion_x(t_vec3d *a, t_flt angle);
t_vec3d			vec_rotaion_y(t_vec3d *a, t_flt angle);
t_vec3d			vec_rotaion_z(t_vec3d *a, t_flt angle);
t_flt			vec_getsquare_length(const t_vec3d *a);
t_flt			vec_dotproduct(const t_vec3d *a, const t_vec3d *b);
void			vec_init(t_vec3d *a, t_flt x, t_flt y, t_flt z);
void			vec_display(t_vec3d *a);
void			vec_normalize(t_vec3d *a);
void			vec_translate(t_vec3d *vec, t_flt tx, t_flt ty, t_flt tz);
void			vec_rotate(t_vec3d *vec, t_flt rx, t_flt ry, t_flt rz);
void			vec_matscale(t_vec3d *vec, t_flt tx, t_flt ty, t_flt tz);

#endif
