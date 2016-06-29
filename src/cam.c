#include "cam.h"

void	xyratio(FLOAT *x, FLOAT *y, const t_cam *cam, const int width, const int height)
{
	*x = cam->wfov / (FLOAT)width;
	*y = cam->hfov / (FLOAT)height;
}

t_vec3d	getupleft(t_cam *cam, FLOAT wfov, FLOAT hfov)
{
	t_vec3d	v1;
	t_vec3d	v2;
	t_vec3d	v3;
	t_vec3d	v4;
	t_vec3d	v5;
	t_vec3d	v6;

	v1 = vec_scale(&cam->dirvec, 1.0f);
	v2 = vec_scale(&cam->upvec, wfov/2.0f);
	v3 = vec_add(&v1, &v2);
	v4 = vec_scale(&cam->rightvec, hfov/2.0f);
	v5 = vec_sub(&v3, &v4);
	v6 = vec_add(&cam->pos, &v5);
	return (v6);
	/*lookat = vec_add(&camPos, (vec_sub(vec_add(vec_scale(&vecdir, 1.0f), (vec_scale(&upvec, 0.5f/2.0f))), vec_scale(&rightvec, 0.35f/2.0f))));*/
}

t_vec3d	getplanepix(t_cam *cam, FLOAT x, FLOAT y, FLOAT xindent, FLOAT yindent)
{
	t_vec3d	v1;
	t_vec3d	v2;
	t_vec3d	v3;
	t_vec3d	v4;
	t_vec3d	v5;

	v1 = vec_scale(&cam->rightvec, xindent * x);
	v2 = vec_scale(&cam->upvec, yindent * y);
	v3 = vec_add(&cam->viewplane_upleft, &v1);
	v4 = vec_sub(&v3, &v2);
	v5 = vec_sub(&v4, &cam->pos);
	return v5;
 /*viewPlaneUpLeft + rightVec*xIndent*x - upVec*yIndent*y*/
}

void	rot_cam(t_cam *cam, FLOAT xa, FLOAT ya, FLOAT za)
{
	cam->dirvec = vec_rotaion_x(&cam->dirvec, xa);
	cam->upvec = vec_rotaion_x(&cam->upvec, xa);
	cam->rightvec = vec_rotaion_x(&cam->rightvec, xa);

	cam->dirvec = vec_rotaion_y(&cam->dirvec, ya);
	cam->upvec = vec_rotaion_y(&cam->upvec, ya);
	cam->rightvec = vec_rotaion_y(&cam->rightvec, ya);

	cam->dirvec = vec_rotaion_z(&cam->dirvec, za);
	cam->upvec = vec_rotaion_z(&cam->upvec, za);
	cam->rightvec = vec_rotaion_z(&cam->rightvec, za);
}

void	move_cam(t_cam *cam, t_vec3d *dir, FLOAT a)
{
	cam->pos.x += dir->x * a;
	cam->pos.y += dir->y * a;
	cam->pos.z += dir->z * a;
}

void	handle_move(t_cam *cam, int key, FLOAT frame)
{
	t_vec3d		dir;

	vec_init(&dir, 0, 0,0);
	if(key & UP)
		dir = vec_sub(&dir, &cam->dirvec);
	if(key & DOWN)
		dir = cam->dirvec;
	if(key & LEFT)
		dir = vec_sub(&dir, &cam->rightvec);
	if(key & RIGHT)
		dir = vec_add(&dir, &cam->rightvec);
	(void)frame;
	/*vec_normalize(&dir);*/
	/*move_cam(cam, &dir, frame);*/
	if(key & ROTPX)
	{
		vec_display(&cam->dirvec);
		rot_cam(cam, 0, 0.1, 0);
		vec_display(&cam->dirvec);
		key -=ROTPX;
	}

}
