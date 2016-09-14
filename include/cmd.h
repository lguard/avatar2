#ifndef CMD_H
# define CMD_H

#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "light.h"
#include "mysdl.h"
#include "save.h"

void	new_obj(t_env *env, char **cmd);
void	delete_obj(t_env *env, char **cmd);
void	delete_light(t_env *env, char **cmd);

void	save_to_file(t_env *env, char **cmd);
void	load_from_file(t_env *e, char **cmd);

void	mod_color(t_color *color, char **cmd);
void	mod_vec3d(t_vec3d *matt, char **cmd);
void	mod_obj(t_env *env, char **cmd);

void	display_scene(t_env *env);
void	display_object(t_scene *sc);
void	display_light(t_scene *sc);

void	exec_cmd(t_env *env, char **cmd);
void	*parse_cmd(void	*env);

void		read_scene(const char *pathname, t_scene *scene);

#endif /* CMD_H */
