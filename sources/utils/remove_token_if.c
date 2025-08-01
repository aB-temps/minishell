/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/01 04:46:32 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parsing.h"

static void	update_token_vector(t_input *input, t_vector *new_vec)
{
	clear_vector(&(input->v_tokens));
	input->v_tokens = new_vec;
	input->token_qty = input->v_tokens->nb_elements;
}

static size_t	count_valid_tokens(ssize_t qty, t_token *array,
		bool(remove_condition)(t_token *array, ssize_t i))
{
	ssize_t	i;
	size_t	valid_tokens;

	i = 0;
	valid_tokens = 0;
	while (i < qty)
	{
		if (remove_condition(array, i))
			valid_tokens++;
		i++;
	}
	return (valid_tokens);
}

void	remove_token_if(t_input *input, t_token **array,
		bool (*remove_condition)(t_token *array, ssize_t i))
{
	t_vector	*new_vec;
	t_token		token;
	ssize_t		i;

	i = 0;
	new_vec = create_vector(count_valid_tokens(input->token_qty, *array,
				remove_condition), sizeof(t_token), clear_token);
	if (!new_vec)
		exit_minishell(input, EXIT_FAILURE);
	while (i < input->token_qty)
	{
		if (remove_condition(*array, i))
		{
			init_token(&token);
			token = dup_token((*array)[i]);
			if (token.type == -1 || !add_element(new_vec, &token))
			{
				clear_vector(&new_vec);
				exit_minishell(input, EXIT_FAILURE);
			}
		}
		i++;
	}
	update_token_vector(input, new_vec);
	*array = (t_token *)input->v_tokens->array;
}
