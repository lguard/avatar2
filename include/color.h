#ifndef COLOR_H
# define COLOR_H

# include "rt.h"

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
#endif

typedef struct	s_color
{
	FLOAT	r;
	FLOAT	g;
	FLOAT	b;
}				t_color;

void	color_scale(t_color *color, FLOAT x);
void	color_add(t_color *colora, t_color *colorb);
void	color_init(t_color *color, FLOAT r, FLOAT g, FLOAT b);

#endif /* COLOR_H */
