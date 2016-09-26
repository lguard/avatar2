/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:13:38 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:23:36 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (*root == NULL)
	{
		*root = list_new(data);
	}
	else
	{
		ptr = *root;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = list_new(data);
	}
}

void	list_pushfront(t_list **root, void *data)
{
	t_list	*ptr;

	if (*root == NULL)
	{
		*root = list_new(data);
	}
	else
	{
		ptr = list_new(data);
		ptr->next = (*root);
		*root = ptr;
	}
}
