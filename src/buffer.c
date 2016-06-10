#include "buffer.h"

void	buffer_init(t_buffer *buff)
{
	buff->a = NULL;
	buff->b = NULL;
	buff->width = 0;
	buff->height = 0;
	buff->aa = 1;
}

void	buffer_reload(t_buffer *buff, size_t width, size_t height, int aa)
{
	if (buff->a)
		buffer_free(buff);
	buffer_create(buff, width, height, aa);
}

void	buffer_free(t_buffer *buff)
{
	size_t		i;

	i = 0;
	while (i < buff->width)
	{
		free(buff->a[i]);
		++i;
	}
	free(buff->a);
	buff->a = NULL;
	i = 0;
	while (i < buff->width * buff->aa)
	{
		free(buff->b[i]);
		++i;
	}
	free(buff->b);
	buff->b = NULL;
}

void	buffer_new(t_color **a, size_t width, size_t height)
{
	t_color		*b;
	size_t	i;

	i = 0;
	b = (t_color*)malloc(sizeof(t_color) * width * height);
	a = (t_color**)malloc(sizeof(t_color*) * width);

	while (i < width)
	{
		a[i] = b + (i*height);
		++i;
	}
}

void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa)
{
	aa = buffer_check_aa(aa);
	buffer_new(buff->a, width, height);
	buffer_new(buff->b, width*aa, height*aa);
	buff->width = width;
	buff->height = height;
	buff->aa = aa;
}

void	buffer_ss(t_buffer *buff)
{
	size_t	x;
	size_t	y;
	double	ratio;

	ratio = 1.f / (double)(buff->aa * buff->aa);
	x = 0;
	while (x < buff->width)
	{
		y = 0;
		while (y < buff->height) {
			buffer_somme_color(buff, x, y, ratio);
		}
	}
}

void	buffer_somme_color(t_buffer *buff, size_t i, size_t j, double ratio)
{
	size_t	x;
	size_t	y;

	x = i * buff->aa;
	color_init(&buff->a[i][j], 0, 0 ,0);
	while (x < (i * buff->aa + buff->aa))//todo a opti d'urgence
	{
		y = j * buff->aa;
		while (y < (j * buff->aa + buff->aa)) {
			buff->a[i][j].r+= buff->b[x][y].r * ratio;
			buff->a[i][j].g+= buff->b[x][y].g * ratio;
			buff->a[i][j].b+= buff->b[x][y].b * ratio;
			++y;
		}
		++x;
	}
	return ;
}

int		buffer_check_aa(int aa)
{
	if ((aa == 1) || (aa == 2) || (aa == 4) || (aa == 8) || (aa == 16))
		return aa;
	return 1;
}
