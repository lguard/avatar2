#include "cmd.h"

void	new_obj(t_env *env, char **cmd)
{
	t_vec3d		pos;

	if(!cmd[1] || !cmd[2] || !cmd[3] || !cmd[4]) 
		return ;
	vec_init(&pos, ft_ftoi(cmd[2]), ft_ftoi(cmd[3]), ft_ftoi(cmd[4]));
	if(*cmd[1] == 'S')
		addobject(&env->scene.obj, surface_default_sphere(&pos), 'S');
	if(*cmd[1] == 'h')
		addobject(&env->scene.obj, surface_default_hyperboloid(&pos), 'h');
	if(*cmd[1] == 'C')
		addobject(&env->scene.obj, surface_default_cylindre(&pos), 'C');
	if(*cmd[1] == 'c')
		addobject(&env->scene.obj, surface_default_cone(&pos), 'c');
	if(*cmd[1] == 'p')
		addobject(&env->scene.obj, surface_default_plane(&pos), 'p');
	env->toraytrace = 1;
}

void	delete_obj(t_env *env, char **cmd)
{
	uint16_t	id;

	if(!cmd[1])
		return ;
	id = ft_atoi(cmd[1]);
	list_delelem(&env->scene.obj, &id, &remove_obj, &delete_object);
	env->toraytrace = 1;
}
