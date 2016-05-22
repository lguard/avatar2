#ifndef CAM_H
# define CAM_H

#include "vec.h"

typedef struct	s_cam;
{
	t_vec3d		pos;
	t_vec3d		upvec;
	t_vec3d		rightvec;
	t_vec3d		dirvec;
	double		wfov;
	double		hfov;
	double		distance;
}				t_cam;

#endif
