/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:55:01 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 13:55:41 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ptr_replace(void **from, void *to)
{
	if (*from)
	{
		free(*from);
		*from = (void *)0;
	}
	return (to);
}
