/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:13:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/22 23:27:13 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *prev, t_list *to_del, void (*del)(void *))
{
	if (prev && to_del && del)
	{
		prev->next = to_del->next;
		del(to_del->content);
		free(to_del);
	}
}
