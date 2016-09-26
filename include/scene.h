/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:23:58 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 15:24:30 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vec.h"
# include "cam.h"
# include "object.h"
# include "list.h"
# include "rt.h"

typedef struct	s_scene
{
	int		width;
	int		height;
	int		render_width;
	int		render_height;
	t_list	*obj;
	t_list	*light;
	t_color	ambiant;
	t_cam	cam;
	int		reflect;
	int		progressbar;
	int		opti;
}				t_scene;

void			init_scene(t_scene *scene, int width, int height);

#endif
