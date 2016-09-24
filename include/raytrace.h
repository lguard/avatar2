#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "object.h"
# include "ray.h"
# include "rt.h"
# include "scene.h"
# include "mysdl.h"
# include "buffer.h"
# include "light.h"

void	ray_trace(t_ray *ray, t_list *obj, t_hit *hit);

void	process_hit(t_hit *hit, t_list *objlist);
void	foreach_light(t_scene *sc, t_hit *hit, t_color *cla, FLOAT rc);
void	light_and_reflect(t_ray *ray, t_hit *hit, t_scene *sc, t_color *cla);
void	rt(t_scene *sc, t_color **a);
int		mainrt(t_env *e, t_scene *scene, t_buffer *buff);

void	pbar(int x, int y, t_scene *sc);

void	render(t_env *e, t_scene *scene, t_color **a);

#endif /* RAYTRACE_H */
