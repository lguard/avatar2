#ifndef LIGHT_H
# define LIGHT_H

# include <string.h>
# include <stdint.h>
# include "vec.h"
# include "ray.h"
# include "raytrace.h"
# include "scene.h"
# include "mtl.h"
# include "rt.h"

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
#endif

# ifndef MAX
#  define MAX(a,b) (((a)>(b))?(a):(b))
#endif

typedef struct	s_dotlight
{
	uint16_t	id;
	t_vec3d		pos;
	t_color		color;
}				t_dotlight;

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_color color);
void	dotlight(t_color *color, t_dotlight *light, t_hit *hit, t_scene *sc);
void	lambert(t_color *cl, t_dotlight *light, t_hit *hit, t_ray *ray);
void	phong(t_color *cl, t_dotlight *light, t_hit *hit, t_ray *ray);
void	addolight(t_list **lightlist, t_dotlight *object);
void	light_free(void *obj);
int		remove_light(void *obj, void *id);
t_dotlight	*getlight_by_id(int id, t_list *lightlst);
t_dotlight	*light_default_dotlight(t_vec3d *pos);

#endif /* LIGHT_H */
