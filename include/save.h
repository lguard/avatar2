#ifndef SAVE_H
# define SAVE_H


# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include "scene.h"
# include "object.h"
# include "light.h"

void		value_to_file(int fd, void *v, int16_t size, int16_t type);
void		write_s(const char *pathname, t_scene *e);

#endif /* SAVE_H */
