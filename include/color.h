#ifndef COLOR_H
# define COLOR_H

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
#endif

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

void	color_scale(t_color *color, double x);
void	color_add(t_color *colora, t_color *colorb);
void	color_init(t_color *color, double r, double g, double b);

#endif /* COLOR_H */
