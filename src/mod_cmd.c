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

void	mod_obj(t_env *env, char **cmd)
{
	t_obj			*obj;
	t_obj_header	*head;

	if (!cmd[1] || !cmd[2] || !cmd[3])
		return ;
	obj = getobject_by_id(ft_atoi(cmd[1]), env->scene.obj);
	head = (t_obj_header*)obj->object;
	if (!ft_strcmp(cmd[2], "color"))
		mod_color(&head->mtl.color, cmd);
	if (!ft_strcmp(cmd[2], "specular"))
		mod_color(&head->mtl.specular, cmd);
	if (!ft_strcmp(cmd[2], "matt"))
		mod_vec3d(&head->matt, cmd);
	if (!ft_strcmp(cmd[2], "matr"))
		mod_vec3d(&head->matr, cmd);
	env->toraytrace = 1;
}
