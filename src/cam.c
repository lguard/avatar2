#include "cam.h"

void	xyratio(double *x, double *y, const t_cam *cam, const t_scene *scene)
{
	*x = cam->wfov / (double)scene->width;
	*y = cam->hfov / (double)scene->height;
}

t_vec3d	getupleft(t_cam *cam)
{
	t_vec3d	v1;
	t_vec3d	v2;
	t_vec3d	v3;
	t_vec3d	v4;
	t_vec3d	v5;
	t_vec3d	v6;

	v1 = vec_scale(&cam->dirvec, 1.0f);
	v2 = vec_scale(&cam->upvec, 0.5f/2.0f);
	v3 = vec_add(&v1, &v2);
	v4 = vec_scale(&cam->rightvec, 0.35f/2.0f);
	v5 = vec_sub(&v3, &v4);
	v6 = vec_add(&cam->pos, &v5);
	return (v6);
	/*lookat = vec_add(&camPos, (vec_sub(vec_add(vec_scale(&vecdir, 1.0f), (vec_scale(&upvec, 0.5f/2.0f))), vec_scale(&rightvec, 0.35f/2.0f))));*/
}

t_vec3d	getplanepix(t_cam *cam, double x, double y, double xindent, double yindent)
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
