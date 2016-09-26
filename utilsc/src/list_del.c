/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:23:14 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:23:31 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_delall(t_list **root, void (*del)(void *))
{
	while (*root)
	{
		list_delfirst(root, del);
	}
}

void	list_delfirst(t_list **root, void (*del)(void *))
{
	t_list	*ptr;

	ptr = (*root)->next;
	del((*root)->data);
	free(*root);
	(*root) = ptr;
}

void	list_dellast(t_list **root, void (*del)(void *))
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

void	list_delelem(t_list **r, void *tr,
		int (*cmp)(void *, void *), void (*del)(void *))
{
	t_list **pp;
	t_list *entry;

	pp = r;
	entry = *r;
	while (entry)
	{
		if (!cmp(entry->data, tr))
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
