#include "vec.h"

inline t_vec3d		vec_add(const t_vec3d* a, const t_vec3d* b)
{
	t_vec3d	c;

	c.x = a->x + b->x;
	c.y = a->y + b->y;
	c.z = a->z + b->z;
	return (c);
}
inline t_vec3d		vec_sub(const t_vec3d* a, const t_vec3d* b)
{
	t_vec3d	c;

	c.x = a->x - b->x;
	c.y = a->y - b->y;
	c.z = a->z - b->z;
	return (c);
}

inline t_vec3d		vec_mul(const t_vec3d* a, const t_vec3d* b)
{
	t_vec3d	c;

	c.x = ( a->y * b->z ) - ( a->z * b->y );
	c.y = ( a->z * b->x ) - ( a->x * b->z );
	c.z = ( a->x * b->y ) - ( a->y * b->x );
	return (c);
}

inline t_vec3d		vec_scale(const t_vec3d* a, const FLOAT f)
{
	t_vec3d	c;

	c.x = a->x * f;
	c.y = a->y * f;
	c.z = a->z * f;
	return (c);
}

inline t_vec3d		vec_reflect(const t_vec3d* a, const t_vec3d* b)
{
	t_vec3d	c;

	c = vec_scale(b, (vec_dotproduct(a, b) * 2.f));
	c = vec_sub(a, &c);
	//todo pas sur que sa soit necessaire de normanlizer
	/*vec_normalize(&c);*/
	return (c);
}

inline FLOAT		vec_getsquare_length(const t_vec3d *a)
{
	return (a->x*a->x + a->y*a->y + a->z*a->z);
}

inline FLOAT		vec_dotproduct(const t_vec3d* a, const t_vec3d* b)
{
	return (a->x*b->x + a->y*b->y + a->z*b->z);
}

inline void		vec_init(t_vec3d* a, FLOAT x, FLOAT y, FLOAT z)
{
	a->x = x;
	a->y = y;
	a->z = z;
	return ;
}

void		vec_display(t_vec3d* a)
{
	printf("\033[32mx%lf | \033[31my%lf | \033[33mz%lf\033[0m\n", a->x, a->y, a->z);
}

inline void		vec_normalize(t_vec3d* a)
{
	FLOAT	mag;

	mag = sqrtf(a->x*a->x + a->y*a->y + a->z*a->z);
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
	return ;
}

/* Xrot mat
 * [  1   0    0  ]
 * [  0  cos  -sin]
 * [  0  sin  cos ]
*/

t_vec3d	vec_rotaion_x(t_vec3d *a, FLOAT angle)
{
	t_vec3d	b;

	b.x = a->x;
	b.y = cos(angle)*a->y - sin(angle)*a->z;
	b.z = sin(angle)*a->y + cos(angle)*a->z;
	return b;
}

/* Yrot mat
 * [ cos  0  sin ]
 * [  0   1   0  ]
 * [-sin  0  cos ]
*/
t_vec3d	vec_rotaion_y(t_vec3d *a, FLOAT angle)
{
	t_vec3d	b;

	b.x = cos(angle)*a->x + sin(angle)*a->z;
	b.y = a->y;
	b.z = -(sin(angle)*a->x) + cos(angle)*a->z;
	return b;
}

/* Zrot mat
 * [ cos  -sin 0  ]
 * [ sin  cos  0  ]
 * [  0   0    1  ]
*/
t_vec3d	vec_rotaion_z(t_vec3d *a, FLOAT angle)
{
	t_vec3d	b;

	b.x = cos(angle)*a->x - sin(angle)*a->y;
	b.y = sin(angle)*a->x + cos(angle)*a->y;
	b.z = a->z;
	return b;
}
