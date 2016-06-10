#include "color.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

void	color_scale(t_color *color, double x)
{
	color->r *= x;
	color->g *= x;
	color->b *= x;
}

void	color_add(t_color *colora, t_color *colorb)
{
	colora->r = MIN(1.0f, colora->r + colorb->r);
	colora->g = MIN(1.0f, colora->g + colorb->g);
	colora->b = MIN(1.0f, colora->b + colorb->b);
}

void	color_init(t_color *color, double r, double g, double b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
