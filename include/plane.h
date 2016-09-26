/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:12:50 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:13:35 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <stdint.h>
# include "vec.h"
# include "ray.h"
# include "mtl.h"
# include "rt.h"

typedef struct	s_plane
{
	uint16_t	id;
	t_mtl		mtl;
	t_vec3d		matt;
	t_vec3d		matr;
	t_vec3d		mats;
	t_vec3d		normal;
	t_vec3d		pos;
}				t_plane;

void			hit_plane(t_ray *ray, void *plane, t_hit *hit);
void			surface_plane(t_ray *ray, void *plane, t_hit *hit);
void			surface_plane_normal(void *plane, t_hit *hit);
t_plane			*surface_default_plane(t_vec3d *pos);

#endif
