/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/01 05:02:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "debug.h"
#include "heredoc.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		exit_minishell(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	if (!check_syntax_error(input))
	{
		ft_putstr_fd(FG_RED "minishell: syntax error\n" R_ALL,
			STDERR_FILENO);
		input->last_exit_status = 2;
		return ((void *)0);
	}
	format_tokens(input);
	format_input(input, (t_token *)input->v_tokens->array);
	handle_heredoc(input);
	return (input);
}
