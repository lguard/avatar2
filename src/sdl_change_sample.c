#include "mysdl.h"

void	change_sample(t_env *e)
{
	e->scene.width = e->scene.render_width * e->buff.aa;
	e->scene.height = e->scene.render_height * e->buff.aa;
	if (e->opti & UNDERSAMPLE)
	{
		e->scene.width = e->scene.render_width / 2;
		e->scene.height = e->scene.render_height / 2;
	}
}

void	change_scenewh(t_env *e, int width, int height)
{
	e->scene.render_width = width;
	e->scene.render_height = height;
	change_sample(e);
	e->scene.cam.wfov = 1.0;
	e->scene.cam.hfov = 1.0 / ((float)width / (float)height);
	e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov,
	e->scene.cam.hfov);
}
