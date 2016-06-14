#ifndef BUFFER_H
# define BUFFER_H

# include "color.h"
# include "stdlib.h"
#include "rt.h"

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
void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa);
void	buffer_ss(t_buffer *buff);
void	buffer_somme_color(t_buffer *buff, size_t i, size_t j, FLOAT ratio);
int		buffer_check_aa(int aa);
t_color	**buffer_new(size_t width, size_t height);
void	buffer_test(void);

#endif /* BUFFER_H */
