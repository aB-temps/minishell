/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:41 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 16:21:59 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*extract_var_key(char *s)
{
	char	*var_key;
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start] && s[start] != '$')
		start++;
	end = start + 1;
	while (s[end] && s[end] != '$' && ft_isalnum(s[end]))
		end++;
	var_key = ft_strndup(s + start, end - start);
	if (!var_key)
		return ((void *)0);
	return (var_key);
}
