#ifndef SCENE_H
# define SCENE_H

# include "vec.h"
# include "cam.h"
# include "object.h"
# include "list.h"

typedef struct	s_scene
{
	int		width;
	int		height;
	t_list *obj;
	t_list *light;
	t_color ambiant;
	t_cam	cam;
}				t_scene;

#endif
