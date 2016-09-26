/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:38 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:01:18 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quad.h"

void	solve_quadratic(t_flt *t, t_flt a, t_flt b, t_flt c)
{
	t_flt	d;

	d = b * b - 4 * a * c;
	if (d < 0.0f)
		return ;
	t[0] = (-b + sqrtf(d)) / (2 * a);
	t[1] = (-b - sqrtf(d)) / (2 * a);
}

t_flt	dot_produce_elips(t_vec3d a, t_vec3d b, t_vec3d c)
{
	return (a.x * b.x * c.x + a.y * b.y * c.y + a.z * b.z * c.z);
}
