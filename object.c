char	*getobjfun(t_obj *obj)
{
	t_objfun a[] = { {'a', "sphere"}, {'b', "plane"}, NULL }
	int		i = 0;

	while (a[i] && obj->type != a[i]->type) {
		++i;
	}
	if (a[i] && a[i]->type == obj->type) {
		return a[i]->name;
	}
	else {
		return NULL;
	}
}
