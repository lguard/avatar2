#ifndef CAM_H
# define CAM_H

#include "vec.h"
#include "rt.h"

typedef struct	s_cam
{
	t_vec3d		pos;
	t_vec3d		dirvec;
	t_vec3d		upvec;
	t_vec3d		rightvec; // temp
	t_vec3d		viewplane_upleft; //temp
	FLOAT		wfov;
	FLOAT		hfov;
	FLOAT		distance;
	FLOAT		roty;
	FLOAT		rotx;
}				t_cam;

/*
**	cam.c
*/
void	xyratio(FLOAT *x, FLOAT *y, const t_cam *c, const int w, const int h);
t_vec3d	getupleft(t_cam *cam, FLOAT wfov, FLOAT hfov);
t_vec3d	getplanepix(t_cam *cam, FLOAT x, FLOAT y, FLOAT xindent, FLOAT yindent);

/*
**	cam.c
*/
void	move_cam(t_cam *cam, t_vec3d *dir, FLOAT a);
void	handle_move(t_cam *cam, int key, FLOAT frame);
void	rot_cam(t_cam *cam);
void	handle_rot(t_cam *cam, int key, FLOAT frame);

#endif
