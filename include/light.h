#ifndef LIGHT_H
# define LIGHT_H

# include "vec.h"
# include "ray.h"
# include "raytrace.h"

#define invsqrtf(x) (1.0f / sqrtf(x))

typedef struct	s_dotlight
{
	t_vec3d		pos;
	t_vec3d		color;
}				t_dotlight;

void	init_dotlight(t_dotlight *light, t_vec3d pos, t_vec3d color);
void	dotlight(t_vec3d *color, t_dotlight *light, t_hit *hit, t_list *objlst);
double	min(double a, double b);

#endif /* LIGHT_H */
