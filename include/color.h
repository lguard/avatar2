/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:06:58 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:21:31 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <math.h>
# include "rt.h"

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
# endif

typedef struct	s_color
{
	t_flt	r;
	t_flt	g;
	t_flt	b;
}				t_color;

void			color_scale(t_color *color, t_flt x);
void			color_add(t_color *colora, t_color *colorb);
void			color_init(t_color *color, t_flt r, t_flt g, t_flt b);
void			color_normalize(t_color *a);

#endif
