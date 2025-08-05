/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 18:04:52 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "heredoc.h"
#include "style.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(1, sizeof(t_token), clear_v_token);
	if (!input->v_tokens)
		exit_parsing(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	// print_input(input, "TOKENIZED");
	if (!check_syntax_error(input))
	{
		print_syntax_error(input);
		return ((void *)0);
	}
	format_tokens(input);
	print_input(input, "FORMATTED TOKENS");
	handle_heredoc(input);
	return (input);
}
