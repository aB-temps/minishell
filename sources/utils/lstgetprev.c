/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstgetprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:48:39 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 08:09:00 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

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
