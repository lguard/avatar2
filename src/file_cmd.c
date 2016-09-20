#include "cmd.h"

void	save_to_file(t_env *e, char **cmd)
{
	if (cmd[1])
	{
		write_s(cmd[1], &e->scene);
		print("save to: %s\n", cmd[1]);
	}
}

void	load_from_file(t_env *e, char **cmd)
{
	if (cmd[1])
	{
		read_scene(cmd[1], &e->scene);
		print("load : %s\n", cmd[1]);
	}
	e->toraytrace = 1;
}
