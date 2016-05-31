#include "object.h"

char	*getobjfun(t_obj *obj)
{
	t_objfun a[] = { {'a', "sphere"}, {'b', "plane"} };
	int		i = 0;

	while (i < 2 && obj->type != a[i].type) {
		++i;
	}
	if (i < 2 && a[i].type == obj->type) {
		return a[i].name;
	}
	else {
		return NULL;
	}
}
