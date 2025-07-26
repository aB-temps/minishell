/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:46:18 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:50:22 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

char	*str_replace(char *s, char *old, char *new)
{
	const size_t	olen = ft_strlen(old);
	const size_t	ttlen = ft_strlen(s) -\
	(countocc(s, old) * olen) + (countocc(s, old) * ft_strlen(new));
	char			*ns;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ns = ft_calloc(sizeof(char), ttlen + 1);
	if (!ns)
		return ((void *)0);
	while (s[i])
	{
		if (!ft_strncmp(&s[i], old, olen))
		{
			i += olen;
			j += ft_strlen(new);
			ft_strlcat(ns, new, j + 1);
		}
		else
			ns[j++] = s[i++];
	}
	ns[ttlen] = '\0';
	return (ns);
}
