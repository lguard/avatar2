#ifndef CAM_H
# define CAM_H

#include "vec.h"
#include "scene.h"

typedef struct	s_cam
{
	t_vec3d		pos;
	t_vec3d		dirvec;
	t_vec3d		upvec;
	t_vec3d		rightvec; // temp
	t_vec3d		viewplane_upleft; //temp
	double		wfov;
	double		hfov;
	double		distance;
}				t_cam;


void	xyratio(double *, double *, const t_cam *, const t_scene *);
t_vec3d	getupleft(t_cam *);
t_vec3d	getplanepix(t_cam *, double, double, double, double);

#endif
