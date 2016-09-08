#ifndef LIST_H
# define LIST_H

#include <stdlib.h>

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

t_list	*list_new(void*);
void	list_pushback(t_list**, void*);
void	list_pushfront(t_list**, void*);
void	list_delall(t_list**,void(*del)(void *));
void	list_dellast(t_list**,void(*del)(void *));
void	list_delfirst(t_list**,void(*del)(void *));
void	list_delelem(t_list **root, void *to_remove, int(*cmp)(void *, void *), void(*del)(void *));

#endif /* LIST_H */
