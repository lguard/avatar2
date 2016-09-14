#ifndef RT_H
# define RT_H

# define DIFFUSE 1
# define SPECULAR 2
# define REFLECTION 4
# define REFRACTION 8
# define SUPERSAMPLE 16
# define UNDERSAMPLE 32
# define SHADOW 64
# define SCREENSIZE 128

# define UP 1 << 1
# define DOWN 1 << 2
# define LEFT 1 << 3
# define RIGHT 1 << 4

# define ROTPY 1 << 1
# define ROTPYB 1 << 2
# define ROTPX 1 << 3
# define ROTPXB 1 << 4
# define ROTPZ 1 << 5
# define ROTPZB 1 << 6

#include <stdint.h>

typedef float	FLOAT;

uint16_t	get_id(void);

#endif /* RT_H */
