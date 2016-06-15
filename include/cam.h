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
}				t_cam;


void	xyratio(FLOAT *, FLOAT *, const t_cam *, const int width, const int height);
t_vec3d	getupleft(t_cam *, FLOAT , FLOAT);
t_vec3d	getplanepix(t_cam *, FLOAT, FLOAT, FLOAT, FLOAT);
void	rot_cam(t_cam *cam, FLOAT xa, FLOAT ya, FLOAT za);

#endif
