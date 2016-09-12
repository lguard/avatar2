#include "cmd.h"

char	*type_to_char(uint16_t type)
{
	if (type == 1)
		return ("sphe");
	if (type == 2)
		return ("cone");
	if (type == 3)
		return ("cyli");
	if (type == 4)
		return ("hype");
	if (type == 5)
		return ("plan");
	else
		return ("");
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
	t_list			*ptr;
	t_obj			*obj;
	t_obj_header	*head;

	ptr = sc->obj;
	while (ptr)
	{
		obj = (t_obj*)ptr->data;
		head = obj->object;
		print("id:%u, type:%s, pos x:%f y:%f z:%f\n", //,  color:\x1b[31mr%f,\x1b[32mg%f,\x1b[34mb%f\x1b[0m\n",
		obj->id, type_to_char(obj->type), head->matt.x, head->matt.y, head->matt.z);
		ptr = ptr->next;
	}
}

void	display_scene(t_env *env)
{
	display_light(&env->scene);
	display_object(&env->scene);
}
