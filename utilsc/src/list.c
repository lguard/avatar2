#include "list.h"

t_list	*list_new(void *data)
{
	t_list *node;
	node = (t_list*)malloc(sizeof(t_list));
	node->next = NULL;
	node->data = data;
	return (node);
}

void	list_pushback(t_list **root, void *data)
{
	t_list	*ptr;

	if (*root == NULL) {
		*root = list_new(data);
	}
	else
	{
		ptr = *root;
		while (ptr->next) {
			ptr = ptr->next;
		}
		ptr->next = list_new(data);
	}
}

void	list_pushfront(t_list **root, void *data)
{
	t_list	*ptr;

	if (*root == NULL) {
		*root = list_new(data);
	}
	else
	{
		ptr = list_new(data);
		ptr->next = (*root);
		*root = ptr;
	}
}

void	list_delall(t_list ** root, void(*del)(void *))
{
	while (*root) {
		list_delfirst(root, del);
	}
}

void	list_delfirst(t_list **root, void(*del)(void *))
{
	t_list	*ptr;

	ptr = (*root)->next;
	del((*root)->data);
	free(*root);
	(*root) = ptr;
}

void	list_dellast(t_list **root, void(*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr2;

	if ((*root)->next == NULL)
	{
		del((*root)->data);
		free(*root);
		*root = NULL;
	}
	ptr = (*root);
	ptr2 = ptr;
	while (ptr->next)
	{
		ptr2 = ptr;
		ptr = ptr->next;
	}
	del(ptr->data);
	ptr->next = NULL;
	ptr->data = NULL;
	free(ptr);
	ptr2->next = NULL;
}

void	list_delelem(t_list **root, void *to_remove, int(*cmp)(void *, void *), void(*del)(void *))
{
	t_list **pp = root;
	t_list *entry = *root;

	while (entry)
	{
		if (!cmp(entry->data, to_remove))
		{
			*pp = entry->next;
			del(entry->data);
			free(entry);
			return ;
		}
		pp = &entry->next;
		entry = entry->next;
	}
}
