/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:03:13 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:08:19 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
** Xrot mat
** [  1   0    0  ]
** [  0  cos  -sin]
** [  0  sin  cos ]
*/

inline t_vec3d	vec_rotaion_x(t_vec3d *a, t_flt angle)
{
	t_vec3d	b;

	b.x = a->x;
	b.y = cos(angle) * a->y - sin(angle) * a->z;
	b.z = sin(angle) * a->y + cos(angle) * a->z;
	return (b);
}

/*
** Yrot mat
** [ cos  0  sin ]
** [  0   1   0  ]
** [-sin  0  cos ]
*/

inline t_vec3d	vec_rotaion_y(t_vec3d *a, t_flt angle)
{
	t_vec3d	b;

	b.x = cos(angle) * a->x + sin(angle) * a->z;
	b.y = a->y;
	b.z = -(sin(angle) * a->x) + cos(angle) * a->z;
	return (b);
}

/*
** Zrot mat
** [ cos  -sin 0  ]
** [ sin  cos  0  ]
** [  0   0    1  ]
*/

inline t_vec3d	vec_rotaion_z(t_vec3d *a, t_flt angle)
{
	t_vec3d	(b);

	b.x = cos(angle) * a->x - sin(angle) * a->y;
	b.y = sin(angle) * a->x + cos(angle) * a->y;
	b.z = a->z;
	return (b);
}
