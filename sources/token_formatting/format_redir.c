/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 22:24:42 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

void	format_redir(t_input *input, ssize_t *i)
{
	t_token	*array;

	array = (t_token *)input->v_tokens->array;
	if (array[(*i)].type >= REDIR_IN && array[(*i)].type <= HEREDOC)
	{
		if ((*i) + 1 < input->token_qty && array[(*i) + 1].type == ENV_VAR)
		{
			array[(*i)].formatted_content = ft_strdup(array[(*i)
					+ 1].formatted_content);
			if (!array[(*i)].formatted_content)
				exit_minishell(input, EXIT_FAILURE);
			(*i)++;
		}
		else if ((*i) + 1 < input->token_qty && array[(*i) + 1].type >= ARG)
		{
			array[(*i)].formatted_content = ft_strdup(array[(*i)
					+ 1].raw_content);
			if (!array[(*i)].formatted_content)
				exit_minishell(input, EXIT_FAILURE);
			(*i)++;
		}
		(*i)++;
	}
}
