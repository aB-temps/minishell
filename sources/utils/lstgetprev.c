#include "libft.h"

t_list	*lstgetprev(t_list *lst, t_list *elem)
{
	t_list *prev;

	prev = (void *)0;
	while (lst)
	{
		if (lst == elem)
			return (prev);
		prev = lst;
		lst = lst->next;
	}
	return ((void *)0);
}