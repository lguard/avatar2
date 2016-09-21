#include "buffer.h"

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
