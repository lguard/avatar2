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

void	mod_obj(t_obj *obj, char **cmd)
{
	t_obj_header	*head;

	head = (t_obj_header*)obj->object;
	if (!ft_strcmp(cmd[2], "color"))
		mod_color(&head->mtl.color, cmd);
	else if (!ft_strcmp(cmd[2], "specular"))
		mod_color(&head->mtl.specular, cmd);
	else if (!ft_strcmp(cmd[2], "matt"))
		mod_vec3d(&head->matt, cmd);
	else if (!ft_strcmp(cmd[2], "matr"))
		mod_vec3d(&head->matr, cmd);
	else if (!ft_strcmp(cmd[2], "reflect"))
		mod_float(&head->mtl.reflect, cmd);
}

void	mod_obj2(t_obj *obj, char **cmd)
{
	t_quad	*head;

	head = (t_quad*)obj->object;
	if (!ft_strcmp(cmd[2], "a"))
		mod_float(&head->a, cmd);
	else if (!ft_strcmp(cmd[2], "b"))
		mod_float(&head->b, cmd);
	else if (!ft_strcmp(cmd[2], "c"))
		mod_float(&head->c, cmd);
	else if (!ft_strcmp(cmd[2], "r"))
		mod_float(&head->r, cmd);
}

void	mod_light(t_dotlight *light, char **cmd)
{
	if (!ft_strcmp(cmd[2], "color"))
		mod_color(&light->color, cmd);
	else if (!ft_strcmp(cmd[2], "matt"))
		mod_vec3d(&light->pos, cmd);
}

void	mod_objlight(t_env *env, char **cmd)
{
	t_obj		*obj;
	t_dotlight	*light;

	if (!cmd[1] || !cmd[2] || !cmd[3])
		return ;
	obj = getobject_by_id(ft_atoi(cmd[1]), env->scene.obj);
	light = getlight_by_id(ft_atoi(cmd[1]), env->scene.light);
	if (obj)
	{
		mod_obj(obj, cmd);
		if (obj->type != 5)
			mod_obj2(obj, cmd);
	}
	else if (light)
		mod_light(light, cmd);
	env->toraytrace = 1;
}
