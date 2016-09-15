#include "cmd.h"

void	exec_cmd(t_env *env, char **cmd)
{
	int		i;

	if (!ft_strcmp(*cmd, "new"))
		new_obj(env, cmd);
	else if (!ft_strcmp(*cmd, "list"))
		display_scene(env);
	else if (!ft_strcmp(*cmd, "mod"))
		mod_obj(env, cmd);
	else if (!ft_strcmp(*cmd, "save"))
		save_to_file(env, cmd);
	else if (!ft_strcmp(*cmd, "load"))
		load_from_file(env, cmd);
	else if (!ft_strcmp(*cmd, "delete") || !ft_strcmp(*cmd, "d"))
		delete_obj(env, cmd);
	else if (!ft_strcmp(*cmd, "quit"))
		env->lol = 1;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}

void	*parse_cmd(void *env)
{
	char *inpt;

	while (42)
	{
		inpt = readline("\x1b[32mavatar2->\x1b[0m");
		add_history(inpt);
		if (!*inpt)
			continue ;
		pthread_mutex_lock(&((t_env*)env)->mutex_lock);
		exec_cmd(((t_env*)env), ft_strsplit(inpt, ' '));
		pthread_mutex_unlock(&((t_env*)env)->mutex_lock);
	}
	clear_history();
	return (NULL);
}