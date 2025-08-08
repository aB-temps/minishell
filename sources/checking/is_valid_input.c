/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:12:10 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:09:57 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"
#include "style.h"
#include <unistd.h>

static enum e_bool	are_quotes_paired(char *s)
{
	size_t	i;
	size_t	s_quotes;
	size_t	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (s[i])
	{
		if (d_quotes % 2 == 0 && s[i] == '\'')
			s_quotes++;
		else if (s_quotes % 2 == 0 && s[i] == '\"')
			d_quotes++;
		i++;
	}
	return (s_quotes % 2 == 0 && d_quotes % 2 == 0);
}

enum e_bool	is_valid_input(char *line, t_input *input)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(line))
		return (FALSE);
	if (!are_quotes_paired(line))
	{
		print_syntax_error(input);
		return (FALSE);
	}
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
