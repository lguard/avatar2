#include "mysdl.h"
#include "light.h"
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"


int mainrt(t_env *e, t_scene *scene, t_buffer *buff, int opti);
void	init_scene(t_scene *scene, int width, int height);
void	handle_move(t_cam *cam, int key, FLOAT frame);
void	handle_rot(t_cam *cam, int key, FLOAT frame);

int		sdl_main_loop(t_env *e)
{
	int		opti;
	int		w;
	int		h;
	int		lol;

	e->opti = 0;
	e->opti |= DIFFUSE;
	e->opti |= UNDERSAMPLE;
	e->opti |= SCREENSIZE;
	e->opti |= SHADOW;

	SDL_StopTextInput();
	SDL_SetRenderDrawColor(e->img, 0, 0, 0, 255);
	SDL_RenderClear(e->img);
	lol = 1;

	while (1)
	{
		if (sdl_events(e))
			return (0);
		if (e->opti & SCREENSIZE)
		{
			SDL_GetWindowSize(e->sc, &w, &h);
			buffer_reload(&e->buff, w, h, e->buff.aa);
			change_scenewh(e, w, h);
			e->opti ^= SCREENSIZE;
		}
		if (e->toraytrace)
		{
			e->toraytrace = 0;
			opti = e->opti;
			struct timeval time;
			if(gettimeofday( &time, 0 ))
				return -1;
			long cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec1 = cur_time / 1000000.0;
			mainrt(e, &e->scene, &e->buff, opti);
			if(gettimeofday( &time, 0 ))
				return -1;
			cur_time = 1000000 * time.tv_sec + time.tv_usec;
			double sec2 = cur_time / 1000000.0;
			/*printf("%f\n", sec2-sec1);*/
			if (e->key != 0) {
				handle_move(&e->scene.cam, e->key, (sec2-sec1)*240);
			}
			if (e->rotkey != 0) {
				handle_rot(&e->scene.cam, e->rotkey, (sec2-sec1)*4);
			}
			e->scene.cam.viewplane_upleft = getupleft(&e->scene.cam, e->scene.cam.wfov, e->scene.cam.hfov);
		}
		SDL_RenderPresent(e->img);
	}
	sdl_quit(e);
}

int		sdl_init(t_env *e, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	e->sc = SDL_CreateWindow("avatar2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	width, height, SDL_WINDOW_RESIZABLE);
	e->img = SDL_CreateRenderer(e->sc, 1, SDL_RENDERER_ACCELERATED);
	e->key = 0;
	e->rotkey = 0;
	for (int i = 0;i < 255;++i)
		e->cmd[i] = 0;
	e->cmd_cursor = 0;
	e->toraytrace = 1;
	return (0);
}

void	init(t_env *e, t_scene *sc, t_buffer *buff, int width, int height)
{
	sdl_init(e, width, height);
	init_scene(sc, width, height);
	buffer_init(buff);
}

void	sdl_quit(t_env *e)
{
	SDL_DestroyWindow(e->sc);
	SDL_Quit();
}


void	save_to_file(char **cmd)
{
	if (cmd[1])
	{
		printf("save to: %s\n", cmd[1]);
	}
}

void	display_light(t_scene *sc)
{
	t_list		*ptr;
	t_dotlight	*dl;

	ptr = sc->light;
	while (ptr)
	{
		dl = (t_dotlight*)ptr->data;
		print("pos:x%f,y%fz,%f color:\x1b[31mr%f,\x1b[32mg%f,\x1b[34mb%f\x1b[0m\n",
		dl->pos.x,dl->pos.y,dl->pos.z,dl->color.g,dl->color.r,dl->color.b);
		ptr = ptr->next;
	}
}

void	display_object(t_scene *sc)
{
	t_list		*ptr;
	t_obj		*obj;

	ptr = sc->obj;
	while (ptr)
	{
		obj = (t_obj*)ptr->data;
		print("id:%u, type:%c\n", //,  color:\x1b[31mr%f,\x1b[32mg%f,\x1b[34mb%f\x1b[0m\n",
		obj->id, obj->type);
		ptr = ptr->next;
	}
}

void	display_scene(t_env *env)
{
	display_light(&env->scene);
	display_object(&env->scene);
}

void	delete_obj(t_env *env, char **cmd)
{
	uint16_t	id;

	if(!cmd[1])
		return ;
	id = ft_atoi(cmd[1]);
	list_delelem(&env->scene.obj, &id, &remove_obj, &delete_object);
	env->toraytrace = 1;
	display_object(&env->scene);
}

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
	display_object(&env->scene);
}

void	exec_cmd(t_env *env, char **cmd)
{
	int		i;
	if (!ft_strcmp(*cmd, "new"))
		new_obj(env, cmd);
	if (!ft_strcmp(*cmd, "list"))
		display_scene(env);
	/*list*/
	/*if (!strcmp(*cmd, "mod"))*/
	/*mod id [color vec, specular vec, mat[t,r,s] vec, reflect f, [abcr] f]*/
	if (!ft_strcmp(*cmd, "save"))
		save_to_file(cmd);
	if (!ft_strcmp(*cmd, "delete") || !ft_strcmp(*cmd, "d"))
		delete_obj(env, cmd);
	/*save filename*/
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}

void	*parse_cmd(void	*env)
{
	char *inpt;

	while (42)
	{
		inpt = readline("\x1b[32mavatar2->\x1b[0m");
		add_history(inpt);
		if (!*inpt)
			continue ;
		exec_cmd(((t_env*)env), ft_strsplit(inpt, ' '));
	}
	clear_history();
	return NULL;
}

int main(void)
{
	t_env		e;
	pthread_t	p;

	init(&e, &e.scene, &e.buff, 400, 500);
	pthread_create (&p, NULL, parse_cmd, &e);
	sdl_main_loop(&e);
	return 0;
}
