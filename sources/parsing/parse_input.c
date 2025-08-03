/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/03 16:09:14 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "heredoc.h"
#include "debug.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		exit_parsing(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	print_input(input, "TOKENIZED");
	if (!check_syntax_error(input))
	{
		ft_putstr_fd(FG_RED "minishell: syntax error\n" R_ALL,
			STDERR_FILENO);
		input->last_exit_status = 2;
		return ((void *)0);
	}
	format_tokens(input);
	print_input(input, "FORMAT TOKENS");
	format_input(input, (t_token *)input->v_tokens->array);
	print_input(input, "FORMAT INPUT");
	handle_heredoc(input);
	return (input);
}
