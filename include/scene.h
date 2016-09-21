#ifndef SCENE_H
# define SCENE_H

# include "vec.h"
# include "cam.h"
# include "object.h"
# include "list.h"
# include "rt.h"

typedef struct	s_scene
{
	int		width;
	int		height;
	int		render_width;
	int		render_height;
	t_list *obj;
	t_list *light;
	t_color ambiant;
	t_cam	cam;
	int		reflect;
	int		progressbar;
	int		opti;
}				t_scene;

#endif
