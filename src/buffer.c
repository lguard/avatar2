#include "buffer.h"
#include "stdio.h"

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
	free(buff->a[0]);
	free(buff->a);
	free(buff->b[0]);
	free(buff->b);
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
		a[i] = b + (i*height);
		++i;
	}
	return a;
}

void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa)
{
	aa = buffer_check_aa(aa);
	buff->a = buffer_new(width, height);
	buff->b = buffer_new(width*aa, height*aa);
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
			++y;
		}
		++x;
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
