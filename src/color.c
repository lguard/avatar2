/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:35:43 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:35:44 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

inline void	color_scale(t_color *color, t_flt x)
{
	color->r *= x;
	color->g *= x;
	color->b *= x;
}

inline void	color_add(t_color *colora, t_color *colorb)
{
	colora->r = MIN(1.0f, colora->r + colorb->r);
	colora->g = MIN(1.0f, colora->g + colorb->g);
	colora->b = MIN(1.0f, colora->b + colorb->b);
}

inline void	color_init(t_color *color, t_flt r, t_flt g, t_flt b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
