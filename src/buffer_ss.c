/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_ss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:01:34 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:01:35 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void	buffer_ss(t_buffer *buff)
{
	size_t	x;
	size_t	y;
	t_flt	ratio;

	ratio = 1.f / (t_flt)(buff->aa * buff->aa);
	x = 0;
	while (x < buff->width)
	{
		y = 0;
		while (y < buff->height)
		{
			buffer_somme_color(buff, x, y, ratio);
			++y;
		}
		++x;
	}
}

void	buffer_us(t_buffer *buff)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < buff->width)
	{
		y = 0;
		while (y < buff->height)
		{
			buff->a[x][y] = buff->c[x / 2][y / 2];
			++y;
		}
		++x;
	}
}

void	buffer_somme_color(t_buffer *buff, size_t i, size_t j, t_flt ratio)
{
	size_t	x;
	size_t	y;
	size_t	si;
	size_t	sj;

	si = i * buff->aa + buff->aa;
	sj = j * buff->aa + buff->aa;
	x = i * buff->aa;
	color_init(&buff->a[i][j], 0, 0, 0);
	while (x < si)
	{
		y = j * buff->aa;
		while (y < sj)
		{
			buff->a[i][j].r += buff->b[x][y].r * ratio;
			buff->a[i][j].g += buff->b[x][y].g * ratio;
			buff->a[i][j].b += buff->b[x][y].b * ratio;
			++y;
		}
		++x;
	}
	return ;
}
