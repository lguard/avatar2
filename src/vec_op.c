/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:02:27 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:03:06 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3d		vec_add(const t_vec3d *a, const t_vec3d *b)
{
	t_vec3d	c;

	c.x = a->x + b->x;
	c.y = a->y + b->y;
	c.z = a->z + b->z;
	return (c);
}

inline t_vec3d		vec_sub(const t_vec3d *a, const t_vec3d *b)
{
	t_vec3d	c;

	c.x = a->x - b->x;
	c.y = a->y - b->y;
	c.z = a->z - b->z;
	return (c);
}

inline t_vec3d		vec_mul(const t_vec3d *a, const t_vec3d *b)
{
	t_vec3d	c;

	c.x = (a->y * b->z) - (a->z * b->y);
	c.y = (a->z * b->x) - (a->x * b->z);
	c.z = (a->x * b->y) - (a->y * b->x);
	return (c);
}

inline t_vec3d		vec_scale(const t_vec3d *a, const t_flt f)
{
	t_vec3d	c;

	c.x = a->x * f;
	c.y = a->y * f;
	c.z = a->z * f;
	return (c);
}

inline t_flt		vec_dotproduct(const t_vec3d *a, const t_vec3d *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
