/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:38:09 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:08:02 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3d	vec_reflect(const t_vec3d *a, const t_vec3d *b)
{
	t_vec3d	c;

	c = vec_scale(b, (vec_dotproduct(a, b) * 2.f));
	c = vec_sub(a, &c);
	vec_normalize(&c);
	return (c);
}

inline t_flt	vec_getsquare_length(const t_vec3d *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

inline void		vec_init(t_vec3d *a, t_flt x, t_flt y, t_flt z)
{
	a->x = x;
	a->y = y;
	a->z = z;
	return ;
}

inline void		vec_normalize(t_vec3d *a)
{
	t_flt	mag;

	mag = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
	if (mag == 0)
		return ;
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
	return ;
}

void			vec_display(t_vec3d *a)
{
	print("\033[32mx%f | \033[31my%f | \033[33mz%f\033[0m\n",
	a->x, a->y, a->z);
}
