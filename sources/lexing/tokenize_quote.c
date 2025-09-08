/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:27:28 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "utils.h"
#include <stdio.h>

void	*tokenize_quote(t_input *input, size_t *i, char *line)
{
	size_t	j;
	int		token_type;
	char	*content;

	j = *i;
	while (!is_quote(line[*i]))
		(*i)++;
	if (line[*i] == '\'')
	{
		quoted_arg_len('\'', i, line);
		token_type = S_QUOTES;
	}
	else
	{
		quoted_arg_len('\"', i, line);
		token_type = D_QUOTES;
	}
	content = ft_strndup(&line[j], (*i) - j);
	if (!content)
		exit_parsing(input, EXIT_FAILURE);
	create_token(input, token_type, content, (line[*i] && !is_operator(line[*i])
			&& !is_whitespace(line[*i])));
	input->token_qty++;
	return (input);
}
