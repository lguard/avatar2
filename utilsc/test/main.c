#include "list.h"
#include "stdio.h"

void	plist(t_list *lst)
{
	while(lst)
	{
		printf("%s--->", (char*)lst->data);
		lst = lst->next;
	}
	printf("%s", "NULL\n");
}

void	dell(void *data)
{
	printf("delete: %s\n", (char*)data);
}

int	main(void)
{
	t_list	*root = list_new("first");
	plist(root);
	list_pushback(&root, "second");
	plist(root);
	list_pushfront(&root, "tresh");
	plist(root);
	list_dellast(&root, &dell);
	plist(root);
	list_pushback(&root, "quatro");
	plist(root);
	list_delall(&root, &dell);
	plist(root);
	return 0;
}