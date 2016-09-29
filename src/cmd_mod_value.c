/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mod_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:39:14 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:39:15 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	mod_color(t_color *color, char **cmd)
{
	if (!cmd[4] || !cmd[5] || !color)
		return ;
	color_init(color, ft_ftoi(cmd[3]), ft_ftoi(cmd[4]), ft_ftoi(cmd[5]));
	color_normalize(color);
}

void	mod_vec3d(t_vec3d *matt, char **cmd)
{
	if (!cmd[4] || !cmd[5] || !matt)
		return ;
	vec_init(matt, ft_ftoi(cmd[3]), ft_ftoi(cmd[4]), ft_ftoi(cmd[5]));
}

void	mod_float(t_flt *f, char **cmd)
{
	*f = ft_ftoi(cmd[3]);
}
