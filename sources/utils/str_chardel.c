/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_chardel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:48:42 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:48:43 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

char	*str_chardel(char *s, char *c)
{
	const size_t	new_total_len = ft_strlen(s) - 1;
	char			*ns;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ns = ft_calloc(new_total_len, sizeof(char));
	if (!ns)
		return ((void *)0);
	while (i < new_total_len)
	{
		if (&s[j] == c)
			j++;
		ns[i++] = s[j++];
	}
	ns[new_total_len] = '\0';
	return (ns);
}
