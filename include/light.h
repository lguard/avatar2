#ifndef LIGHT_H
# define LIGHT_H

# include "vec.h"
# include "ray.h"
# include "raytrace.h"
# include "mtl.h"

#define invsqrtf(x) (1.0f / sqrtf(x))

typedef struct	s_dotlight
{
	t_vec3d		pos;
	t_color		color;
}				t_dotlight;

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_color color);
void	dotlight(t_color *color, t_dotlight *light, t_hit *hit, t_list *objlst);
double	min(double a, double b);

#endif /* LIGHT_H */
