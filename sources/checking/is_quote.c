/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:12:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:10:21 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"

enum e_bool	is_d_quote(char c)
{
	return (c == '"');
}

enum e_bool	is_s_quote(char c)
{
	return (c == '\'');
}

enum e_bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

enum e_bool	is_quoted_arg(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_whitespace(s[i]) && !is_operator(s[i]))
		if (is_quote(s[i++]))
			return (TRUE);
	return (FALSE);
}
