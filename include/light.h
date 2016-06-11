#ifndef LIGHT_H
# define LIGHT_H

# include <string.h>
# include "vec.h"
# include "ray.h"
# include "raytrace.h"
# include "mtl.h"

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
#endif

# ifndef MAX
#  define MAX(a,b) (((a)>(b))?(a):(b))
#endif

typedef struct	s_dotlight
{
	t_vec3d		pos;
	t_color		color;
}				t_dotlight;

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_color color);
void	dotlight(t_color *color, t_dotlight *light, t_hit *hit, t_list *objlst);
void	addolight(t_list **lightlist, t_dotlight *object);
void	delete_light(void *obj);

#endif /* LIGHT_H */
