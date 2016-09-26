/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:09:35 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:21:31 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTL_H
# define MTL_H

# include "color.h"
# include "rt.h"

typedef struct	s_mtl
{
	t_color	color;
	t_color	specular;
	t_flt	reflect;
	t_flt	power;
}				t_mtl;

#endif
