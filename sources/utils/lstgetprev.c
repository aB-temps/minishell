/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstgetprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:48:39 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:48:40 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lstgetprev(t_list *lst, t_list *elem)
{
	t_list	*prev;

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
