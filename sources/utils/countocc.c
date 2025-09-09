/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countocc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:26 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/09 02:55:47 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	countocc(char *s, char *to_find)
{
	size_t	count;
	char	*cursor;

	count = 0;
	cursor = s;
	while (to_find && cursor)
	{
		cursor = ft_strnstr(s, to_find, ft_strlen(s));
		if (cursor)
			count++;
		s = cursor + ft_strlen(to_find);
	}
	return (count);
}
