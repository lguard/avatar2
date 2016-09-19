#include "buffer.h"
#include <stdio.h>

void	buffer_init(t_buffer *buff)
{
	buff->a = NULL;
	buff->b = NULL;
	buff->c = NULL;
	buff->width = 0;
	buff->height = 0;
	buff->aa = 4;
}

void	buffer_reload(t_buffer *buff, size_t width, size_t height, int aa)
{
	if (width <= 0 || height <= 0)
		return ;
	if (buff->a)
		buffer_free(buff);
	buffer_create(buff, width, height, aa);
}

void	buffer_reload_ss(t_buffer *buff, int aa)
{
	free(buff->b[0]);
	free(buff->b);
	aa = buffer_check_aa(aa);
	buff->b = buffer_new(buff->width * aa, buff->height * aa);
	buff->aa = aa;
}

void	buffer_reload_us(t_buffer *buff, int pa)
{
	free(buff->c[0]);
	free(buff->c);
	pa = buffer_check_aa(pa);
	buff->c = buffer_new(buff->width / pa, buff->height / pa);
	buff->pa = pa;
}

void	buffer_free(t_buffer *buff)
{
	free(buff->a[0]);
	free(buff->a);
	free(buff->b[0]);
	free(buff->b);
	free(buff->c[0]);
	free(buff->c);
}

t_color	**buffer_new(size_t width, size_t height)
{
	t_color		*b;
	t_color		**a;
	size_t	i;
	i = 0;
	b = (t_color*)malloc(sizeof(t_color) * width * height);
	a = (t_color**)malloc(sizeof(t_color*) * width);
	while (i < width)
	{
		a[i] = b + (i * height);
		++i;
	}
	return (a);
}

void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa)
{
	aa = buffer_check_aa(aa);
	buff->a = buffer_new(width, height);
	buff->b = buffer_new(width * aa, height * aa);
	buff->c = buffer_new(width / 2 + 1, height / 2 + 1);
	buff->width = width;
	buff->height = height;
	buff->aa = aa;
}

void	buffer_ss(t_buffer *buff)
{
	size_t	x;
	size_t	y;
	FLOAT	ratio;

	ratio = 1.f / (FLOAT)(buff->aa * buff->aa);
	x = 0;
	while (x < buff->width)
	{
		y = 0;
		while (y < buff->height)
		{
			buffer_somme_color(buff, x, y, ratio);
			++y;
		}
		++x;
	}
}

void	buffer_us(t_buffer *buff)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < buff->width)
	{
		y = 0;
		while (y < buff->height)
		{
			buff->a[x][y] = buff->c[x / 2][y / 2];
			++y;
		}
		++x;
	}
}

void	buffer_somme_color(t_buffer *buff, size_t i, size_t j, FLOAT ratio)
{
	size_t	x;
	size_t	y;

	x = i * buff->aa;
	color_init(&buff->a[i][j], 0, 0, 0);
	while (x < (i * buff->aa + buff->aa))//todo a opti d'urgence
	{
		y = j * buff->aa;
		while (y < (j * buff->aa + buff->aa))
		{
			buff->a[i][j].r += buff->b[x][y].r * ratio;
			buff->a[i][j].g += buff->b[x][y].g * ratio;
			buff->a[i][j].b += buff->b[x][y].b * ratio;
			++y;
		}
		++x;
	}
	return ;
}

int		buffer_check_aa(int aa)
{
	if ((aa == 1) || (aa == 2) || (aa == 4)
	|| (aa == 8) || (aa == 16) || (aa == 128))
		return (aa);
	return (1);
}

void	buffer_test(void)
{
	t_buffer buff;

	buffer_init(&buff);
	buffer_reload(&buff, 2, 2, 2);
	printf("[%lf][%lf]\n", buff.a[0][0].r, buff.a[0][1].r);
	printf("[%lf][%lf]\n\n", buff.a[1][0].r, buff.a[1][1].r);
	buff.b[0][0].r = 1, buff.b[0][1].r = 2; buff.b[0][2].r = 3; buff.b[0][3].r = 4;
	buff.b[1][0].r = 1, buff.b[1][1].r = 2; buff.b[1][2].r = 3; buff.b[1][3].r = 4;
	buff.b[2][0].r = 1, buff.b[2][1].r = 2; buff.b[2][2].r = 3; buff.b[2][3].r = 4;
	buff.b[3][0].r = 1, buff.b[3][1].r = 2; buff.b[3][2].r = 3; buff.b[3][3].r = 4;
	printf("[%lf][%lf][%lf][%lf]\n", buff.b[0][0].r, buff.b[0][1].r, buff.b[0][2].r, buff.b[0][3].r);
	printf("[%lf][%lf][%lf][%lf]\n", buff.b[1][0].r, buff.b[1][1].r, buff.b[1][2].r, buff.b[1][3].r);
	printf("[%lf][%lf][%lf][%lf]\n", buff.b[2][0].r, buff.b[2][1].r, buff.b[2][2].r, buff.b[2][3].r);
	printf("[%lf][%lf][%lf][%lf]\n\n", buff.b[3][0].r, buff.b[3][1].r, buff.b[3][2].r, buff.b[3][3].r);
	buffer_ss(&buff);
	printf("[%lf][%lf]\n", buff.a[0][0].r, buff.a[0][1].r);
	printf("[%lf][%lf]\n\n", buff.a[1][0].r, buff.a[1][1].r);
	buffer_free(&buff);
}
