#include "cmd.h"

void	save_to_file(t_env *e, char **cmd)
{
	if (cmd[1])
	{
		write_s(cmd[1], &e->scene);
		printf("save to: %s\n", cmd[1]);
	}
}
