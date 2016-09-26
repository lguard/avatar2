/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_motion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:32:58 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:33:03 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"

void	move_cam(t_cam *cam, t_vec3d *dir, t_flt a)
{
	cam->pos.x += dir->x * a;
	cam->pos.y += dir->y * a;
	cam->pos.z += dir->z * a;
}

void	handle_move(t_cam *cam, int key, t_flt frame)
{
	t_vec3d		dir;

	vec_init(&dir, 0, 0, 0);
	if (key & UP)
		dir = cam->dirvec;
	if (key & DOWN)
		dir = vec_sub(&dir, &cam->dirvec);
	if (key & LEFT)
		dir = vec_sub(&dir, &cam->rightvec);
	if (key & RIGHT)
		dir = vec_add(&dir, &cam->rightvec);
	vec_normalize(&dir);
	move_cam(cam, &dir, frame);
}

/*
**cam->dirvec = vec_rotaion_z(&cam->dirvec, za);
**cam->upvec = vec_rotaion_z(&cam->upvec, za);
**cam->rightvec = vec_rotaion_z(&cam->rightvec, za);
*/

void	rot_cam(t_cam *cam)
{
	vec_init(&cam->dirvec, 0.f, 0.f, 1.f);
	vec_init(&cam->upvec, 0.f, 1.f, 0.f);
	cam->rightvec = vec_mul(&cam->dirvec, &cam->upvec);
	cam->dirvec = vec_rotaion_x(&cam->dirvec, cam->rotx);
	cam->upvec = vec_rotaion_x(&cam->upvec, cam->rotx);
	cam->rightvec = vec_rotaion_x(&cam->rightvec, cam->rotx);
	cam->dirvec = vec_rotaion_y(&cam->dirvec, cam->roty);
	cam->upvec = vec_rotaion_y(&cam->upvec, cam->roty);
	cam->rightvec = vec_rotaion_y(&cam->rightvec, cam->roty);
}

void	handle_rot(t_cam *cam, int key, t_flt frame)
{
	frame *= 0.4;
	if (key & ROTPX)
		cam->rotx -= frame;
	if (key & ROTPXB)
		cam->rotx += frame;
	if (key & ROTPY)
		cam->roty += frame;
	if (key & ROTPYB)
		cam->roty -= frame;
	rot_cam(cam);
}
