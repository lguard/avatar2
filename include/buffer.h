#ifndef BUFFER_H
# define BUFFER_H

# include "color.h"
# include "stdlib.h"
typedef struct	s_buffer
{
	t_color **a;
	t_color **b;
	size_t	width;
	size_t	height;
	int		aa;
}				t_buffer;

void	buffer_init(t_buffer *buff);
void	buffer_reload(t_buffer *buff, size_t width, size_t height, int aa);
void	buffer_free(t_buffer *buff);
void	buffer_new(t_color **a, size_t width, size_t height);
void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa);
int		buffer_check_aa(int aa);

#endif /* BUFFER_H */
