#include "raytrace.h"

void	render(t_env *e, t_scene *scene, t_color **a)
{
	int x;
	int y;
	
	x = 0;
	while(x < scene->render_width)
	{
		y = 0;
		while(y < scene->render_height)
		{
			sdl_putpxl(e, x, y,
			(unsigned char)(a[x][y].r*255.0f),
			(unsigned char)(a[x][y].g*255.0f),
			(unsigned char)(a[x][y].b*255.0f));
			++y;
		}
		++x;
	}
}
