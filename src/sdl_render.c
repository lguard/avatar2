/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:37:39 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 16:35:27 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl.h"

void	sdl_putpxl(t_env *e, int x, int y, t_color cl)
{
	SDL_SetRenderDrawColor(e->img, cl.r, cl.g, cl.b, 255);
	SDL_RenderDrawPoint(e->img, x, y);
}
