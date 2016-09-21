#ifndef CMD_H
# define CMD_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "light.h"
# include "mysdl.h"
# include "scene.h"
# include "object.h"

/*
**	cmd_save_scene.c
*/
void	value_to_file(int fd, void *v, int16_t size, int16_t type);
void	write_s(const char *pathname, t_scene *e);
void	save_to_file(t_env *e, char **cmd);

/*
**	cmd_read_scene.c
*/
int		select_surface(int fd, t_scene *scene, uint16_t type);
void	read_scene(const char *pathname, t_scene *scene);
void	load_from_file(t_env *e, char **cmd);

/*
**	cmd_load_obj.c
*/
void	load_sphere(int fd, t_scene *scene);
void	load_cone(int fd, t_scene *scene);
void	load_cylindre(int fd, t_scene *scene);
void	load_hyperbol(int fd, t_scene *scene);
void	load_plane(int fd, t_scene *scene);

/*
**	cmd_load_scene.c
*/
void	load_light(int fd, t_scene *scene);
void	load_cam(int fd, t_scene *scene);

/*
**	cmd_new_scene.c
*/
void	new_obj(t_env *env, char **cmd);
void	delete_obj(t_env *env, char **cmd);
void	delete_light(t_env *env, char **cmd);

/*
**	cmd_mod_value.c
*/
void	mod_color(t_color *color, char **cmd);
void	mod_vec3d(t_vec3d *matt, char **cmd);
void	mod_float(FLOAT *f, char **cmd);

/*
**	cmd_mod_object.c
*/
void	mod_obj(t_obj *obj, char **cmd);
void	mod_obj2(t_obj *obj, char **cmd);
void	mod_light(t_dotlight *obj, char **cmd);
void	mod_objlight(t_env *env, char **cmd);

/*
**	cmd_display.c
*/
char	*type_to_char(uint16_t type);
void	display_scene(t_env *env);
void	display_object(t_scene *sc);
void	display_light(t_scene *sc);

/*
**	cmd.c
*/
void	change_reflect(t_scene *scene, char **cmd);
void	change_ss(t_env *e, char **cmd);
void	iforest(t_env *env, char **cmd);
void	exec_cmd(t_env *env, char **cmd);
void	*parse_cmd(void	*env);

#endif /* CMD_H */
