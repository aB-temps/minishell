/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:17 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static void	tokenize_redir(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (line[*i] == '>')
	{
		if (*i < line_len - 1 && line[*i + 1] == '>')
		{
			create_token(input, APPEND, ">>", FALSE);
			(*i)++;
		}
		else
			create_token(input, REDIR_OUT, ">", FALSE);
	}
	else if (line[*i] == '<')
	{
		if (*i < line_len - 1 && line[*i + 1] == '<')
		{
			create_token(input, HEREDOC, "<<", FALSE);
			(*i)++;
		}
		else
			create_token(input, REDIR_IN, "<", FALSE);
	}
	(*i)++;
	input->token_qty++;
}

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (line[*i] == '|')
	{
		create_token(input, PIPE, "|", FALSE);
		(*i)++;
		input->token_qty++;
	}
	else
		tokenize_redir(input, i, line, line_len);
}
