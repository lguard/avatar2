/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:58 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:36:05 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	render(t_env *e, t_scene *scene, t_color **a)
{
	int x;
	int y;

	x = 0;
	while (x < scene->render_width)
	{
		y = 0;
		while (y < scene->render_height)
		{
			sdl_putpxl(e, x, y, (t_color){
			(unsigned char)(a[x][y].r * 255.0f),
			(unsigned char)(a[x][y].g * 255.0f),
			(unsigned char)(a[x][y].b * 255.0f)});
			++y;
		}
		++x;
	}
}
