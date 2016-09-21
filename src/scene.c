#include "scene.h"

void	init_scene(t_scene *scene, int width, int height)
{
	vec_init(&scene->cam.pos, 350.f, 10.f, -3000.f);
	vec_init(&scene->cam.dirvec, 0.f, 0.f, 1.f);
	vec_init(&scene->cam.upvec, 0.f, 1.f, 0.f);
	scene->cam.rightvec = vec_mul(&scene->cam.dirvec, &scene->cam.upvec);
	scene->render_width = width;
	scene->render_height = height;
	scene->width = scene->render_width * 1;
	scene->height = scene->render_height * 1;
	scene->cam.wfov = 1.0;
	scene->cam.hfov = 1.0 / ((float)width / (float)height);
	scene->cam.viewplane_upleft =
	getupleft(&scene->cam, scene->cam.wfov, scene->cam.hfov);
	scene->cam.distance = 1.f;
	scene->cam.roty = 0;
	scene->cam.rotx = 0;
}
