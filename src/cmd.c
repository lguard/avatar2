#include "cmd.h"

void	change_reflect(t_scene *scene, char **cmd)
{
	int		r;

	if (!cmd[1])
		return ;
	r = ft_atoi(cmd[1]);
	if (r < 0 || r > 5)
		return ;
	scene->reflect = r+1;
}

void	change_ss(t_env *e, char **cmd)
{
	int		r;

	if (!cmd[1])
		return ;
	r = ft_atoi(cmd[1]);
	buffer_reload(&e->buff, e->scene.render_width,
	e->scene.render_height, r);
	change_scenewh(e, e->scene.render_width, e->scene.render_height);
}

void	iforest(t_env *env, char **cmd)
{
	if (!ft_strcmp(*cmd, "new"))
		new_obj(env, cmd);
	else if (!ft_strcmp(*cmd, "list"))
		display_scene(env);
	else if (!ft_strcmp(*cmd, "mod"))
		mod_objlight(env, cmd);
	else if (!ft_strcmp(*cmd, "save"))
		save_to_file(env, cmd);
	else if (!ft_strcmp(*cmd, "load"))
		load_from_file(env, cmd);
	else if (!ft_strcmp(*cmd, "delete") || !ft_strcmp(*cmd, "d"))
		delete_obj(env, cmd);
	else if (!ft_strcmp(*cmd, "reflect"))
		change_reflect(&env->scene, cmd);
	else if (!ft_strcmp(*cmd, "ss"))
		change_ss(env, cmd);
	else if (!ft_strcmp(*cmd, "quit"))
		env->lol = 1;
	else if (!ft_strcmp(*cmd, "trace"))
	{
		env->toraytrace = 1;
		env->scene.progressbar = 1;
	}
}

void	exec_cmd(t_env *env, char **cmd)
{
	int		i;

	i = 0;
	iforest(env, cmd);
	while (cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}

void	*parse_cmd(void *env)
{
	char	*inpt;
	char	**cmd;
	t_env	*e;

	e = (t_env*)env;
	while (42)
	{
		inpt = readline("\x1b[32mavatar2->\x1b[0m");
		add_history(inpt);
		if (!*inpt)
			continue ;
		pthread_mutex_lock(&e->mutex_lock);
		cmd = ft_strsplit(inpt, ' ');
		if (cmd)
			exec_cmd(e, cmd);
		if (e->lol)
		{
			pthread_mutex_unlock(&e->mutex_lock);
			break ;
		}
		pthread_mutex_unlock(&e->mutex_lock);
	}
	clear_history();
	return (NULL);
}
