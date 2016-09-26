/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:32:10 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:32:54 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"

void	xyratio(t_vec3d *xyi, const t_cam *c, const int w, const int h)
{
	xyi->x = c->wfov / (t_flt)w;
	xyi->y = c->hfov / (t_flt)h;
}

/*
**	lookat = vec_add(&camPos, (vec_sub(vec_add(vec_scale(&vecdir, 1.0f)
**	, (vec_scale(&upvec, 0.5f/2.0f))), vec_scale(&rightvec, 0.35f/2.0f))));
*/

t_vec3d	getupleft(t_cam *cam, t_flt wfov, t_flt hfov)
{
	t_vec3d	v1;
	t_vec3d	v2;
	t_vec3d	v3;
	t_vec3d	v4;
	t_vec3d	v5;

	v1 = vec_scale(&cam->dirvec, 1.0f);
	v2 = vec_scale(&cam->upvec, hfov / 2.0f);
	v3 = vec_add(&v1, &v2);
	v4 = vec_scale(&cam->rightvec, wfov / 2.0f);
	v5 = vec_sub(&v3, &v4);
	v1 = vec_add(&cam->pos, &v5);
	return (v1);
}

/*
**	viewPlaneUpLeft + rightVec*xIndent*x - upVec*yIndent*y
*/

t_vec3d	getplanepix(t_cam *cam, t_flt x, t_flt y, t_vec3d *xyi)
{
	t_vec3d	v1;
	t_vec3d	v2;
	t_vec3d	v3;
	t_vec3d	v4;
	t_vec3d	v5;

	v1 = vec_scale(&cam->rightvec, xyi->x * x);
	v2 = vec_scale(&cam->upvec, xyi->y * y);
	v3 = vec_add(&cam->viewplane_upleft, &v1);
	v4 = vec_sub(&v3, &v2);
	v5 = vec_sub(&v4, &cam->pos);
	vec_normalize(&v5);
	return (v5);
}
