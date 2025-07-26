/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:54:21 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parsing.h"

void	update_token_vector(t_input *input, t_vector *new_vec)
{
	clear_vector(&input->v_tokens);
	input->v_tokens = new_vec;
	input->token_qty = input->v_tokens->capacity;
}

size_t	count_valid_tokens(size_t qty, const t_token *array)
{
	size_t	i;
	size_t	valid_tokens;

	i = 0;
	valid_tokens = 0;
	while (i < qty)
	{
		if (array[i].type >= COMMAND && array[i].type <= HEREDOC)
			valid_tokens++;
		i++;
	}
	return (valid_tokens);
}

void	format_input(t_input *input, t_token *array)
{
	t_vector	*new_vec;
	t_token		token;
	ssize_t		i;

	i = 0;
	new_vec = create_vector(count_valid_tokens(input->token_qty, array),
			sizeof(t_token), clear_token);
	if (!new_vec)
		exit_minishell(input, EXIT_FAILURE);
	while (i < input->token_qty)
	{
		if (array[i].type >= COMMAND && array[i].type <= HEREDOC)
		{
			init_token(&token);
			token = dup_token(array[i]);
			if (token.type == -1 || !add_element(new_vec, &token))
			{
				clear_vector(&new_vec);
				exit_minishell(input, EXIT_FAILURE);
			}
		}
		i++;
	}
	update_token_vector(input, new_vec);
}
