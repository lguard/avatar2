#ifndef BUFFER_H
# define BUFFER_H

# include <stdlib.h>
# include "color.h"
# include "rt.h"

typedef struct	s_buffer
{
	t_color **a;
	t_color **b;
	t_color **c;
	size_t	width;
	size_t	height;
	int		aa;
	int		pa;
}				t_buffer;

/*
**	buffer.c
*/
void	buffer_init(t_buffer *buff);
void	buffer_free(t_buffer *buff);
void	buffer_create(t_buffer *buff, size_t width, size_t height, int aa);
int		buffer_check_aa(int aa);
t_color	**buffer_new(size_t width, size_t height);
/*
**	buffer_ss.c
*/
void	buffer_ss(t_buffer *buff);
void	buffer_us(t_buffer *buff);
void	buffer_somme_color(t_buffer *buff, size_t i, size_t j, FLOAT ratio);
/*
**	buffer_reload.c
*/
void	buffer_reload(t_buffer *buff, size_t width, size_t height, int aa);
void	buffer_reload_ss(t_buffer *buff, int aa);
void	buffer_reload_us(t_buffer *buff, int pa);

#endif /* BUFFER_H */
