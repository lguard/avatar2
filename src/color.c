#include "color.h"

inline void	color_scale(t_color *color, FLOAT x)
{
	color->r *= x;
	color->g *= x;
	color->b *= x;
}

inline void	color_add(t_color *colora, t_color *colorb)
{
	colora->r = MIN(1.0f, colora->r + colorb->r);
	colora->g = MIN(1.0f, colora->g + colorb->g);
	colora->b = MIN(1.0f, colora->b + colorb->b);
}

inline void	color_init(t_color *color, FLOAT r, FLOAT g, FLOAT b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
