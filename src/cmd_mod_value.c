#include "cmd.h"

void	mod_color(t_color *color, char **cmd)
{
	if (!cmd[4] || !cmd[5] || !color)
		return ;
	color_init(color, ft_ftoi(cmd[3]), ft_ftoi(cmd[4]), ft_ftoi(cmd[5]));
}

void	mod_vec3d(t_vec3d *matt, char **cmd)
{
	if (!cmd[4] || !cmd[5] || !matt)
		return ;
	vec_init(matt, ft_ftoi(cmd[3]), ft_ftoi(cmd[4]), ft_ftoi(cmd[5]));
}

void	mod_float(FLOAT *f, char **cmd)
{
	*f = ft_ftoi(cmd[3]);
}
