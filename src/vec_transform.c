/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:05:38 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:06:11 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline void	vec_translate(t_vec3d *vec, t_flt tx, t_flt ty, t_flt tz)
{
	vec->x += tx;
	vec->y += ty;
	vec->z += tz;
}

inline void	vec_rotate(t_vec3d *vec, t_flt rx, t_flt ry, t_flt rz)
{
	*vec = vec_rotaion_x(vec, rx);
	*vec = vec_rotaion_y(vec, ry);
	*vec = vec_rotaion_z(vec, rz);
}

inline void	vec_matscale(t_vec3d *vec, t_flt tx, t_flt ty, t_flt tz)
{
	vec->x *= tx;
	vec->y *= ty;
	vec->z *= tz;
}
