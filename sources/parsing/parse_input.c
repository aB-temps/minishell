/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/04 02:07:27 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "style.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(1, sizeof(t_token), clear_v_token);
	if (!input->v_tokens)
		exit_parsing(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	if (!check_syntax_error(input))
	{
		print_syntax_error(input);
		return ((void *)0);
	}
	format_tokens(input);
	handle_heredoc(input);
	return (input);
}
