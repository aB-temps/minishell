/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 18:17:15 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <stdio.h>

void	quoted_arg_len(char quote, size_t *i, char *line)
{
	size_t	count;

	count = 0;
	while (line[++(*i)])
	{
		if (line[*i] == quote)
		{
			count++;
			while (line[*i] && (count < 2 && !is_whitespace(line[*i])))
			{
				count += (line[*i] == quote);
				(*i)++;
			}
			break ;
		}
	}
}

void	*tokenize_quote(t_input *input, size_t *i, char *line)
{
	ssize_t	j;
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
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, content, (line[*i] && !is_operator(line[*i])
			&& !is_whitespace(line[*i])));
	input->token_qty++;
	return (input);
}
