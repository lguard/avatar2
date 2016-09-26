/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:36:35 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:36:36 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	hit_error(t_ray *ray, void *non, t_hit *hit)
{
	(void)ray;
	(void)non;
	(void)hit;
	print("Error: can't select object function %s\n", __FILE__);
}
