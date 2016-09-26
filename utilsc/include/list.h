/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:24:03 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 17:25:36 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

t_list			*list_new(void *d);
void			list_pushback(t_list **l, void *d);
void			list_pushfront(t_list **l, void *d);
void			list_delall(t_list **l, void(*del)(void *));
void			list_dellast(t_list **l, void(*del)(void *));
void			list_delfirst(t_list **l, void(*del)(void *));
void			list_delelem(t_list **r, void *tr,
				int(*cmp)(void *, void *), void(*del)(void *));

#endif
