#include "buffer.h"
#include <stdio.h>

void	buffer_init(t_buffer *buff)
{
	buff->a = NULL;
	buff->b = NULL;
	buff->c = NULL;
	buff->width = 0;
	buff->height = 0;
	buff->aa = 2;
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

int		buffer_check_aa(int aa)
{
	if ((aa == 1) || (aa == 2) || (aa == 4)
	|| (aa == 8) || (aa == 16) || (aa == 32))
		return (aa);
	return (1);
}
