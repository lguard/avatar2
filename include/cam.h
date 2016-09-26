/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 14:52:44 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:21:31 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H

# include "vec.h"
# include "rt.h"

typedef struct	s_cam
{
	t_vec3d		pos;
	t_vec3d		dirvec;
	t_vec3d		upvec;
	t_vec3d		rightvec;
	t_vec3d		viewplane_upleft;
	t_flt		wfov;
	t_flt		hfov;
	t_flt		distance;
	t_flt		roty;
	t_flt		rotx;
}				t_cam;

/*
**	cam.c
*/
void			xyratio(t_vec3d *xyi, const t_cam *c, const int w, const int h);
t_vec3d			getupleft(t_cam *cam, t_flt wfov, t_flt hfov);
t_vec3d			getplanepix(t_cam *cam, t_flt x, t_flt y, t_vec3d *xyi);

/*
**	cam.c
*/
void			move_cam(t_cam *cam, t_vec3d *dir, t_flt a);
void			handle_move(t_cam *cam, int key, t_flt frame);
void			rot_cam(t_cam *cam);
void			handle_rot(t_cam *cam, int key, t_flt frame);

#endif
