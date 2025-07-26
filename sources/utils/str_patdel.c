/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_patdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:46:36 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:49:38 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

char	*str_patdel(char *s, char *pat)
{
	size_t	new_total_len;
	char	*ns;
	size_t	i;
	size_t	j;

	new_total_len = ft_strlen(s) - (countocc(s, pat) * ft_strlen(pat));
	i = 0;
	j = 0;
	if (new_total_len == ft_strlen(s))
		return (s);
	ns = ft_calloc(sizeof(char), new_total_len + 1);
	if (!ns)
		return ((void *)0);
	while (i < new_total_len)
	{
		while (!ft_strncmp(&s[j], pat, ft_strlen(pat)))
			j += ft_strlen(pat);
		ns[i++] = s[j++];
	}
	ns[new_total_len] = '\0';
	return (ns);
}
