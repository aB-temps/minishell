/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 11:40:21 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static char	*join_to_link_args(t_token *array, size_t i, size_t *j)
{
	char	*content;

	if (array[i].type == ENV_VAR)
		content = ft_strdup(array[i].formatted_content);
	else
		content = ft_strdup(array[i].raw_content);
	if (!content)
		return ((void *)0);
	while (array[i].link_to_next)
	{
		if (array[i + 1].type == ENV_VAR)
			content = str_free_to_join(content, array[i + 1].formatted_content);
		else
			content = str_free_to_join(content, array[i + 1].raw_content);
		if (!content)
			return ((void *)0);
		i++;
		(*j)++;
	}
	return (content);
}

void	format_redir(t_input *input, ssize_t *i)
{
	t_token	*array;
	size_t	j;

	array = (t_token *)input->v_tokens->array;
	j = 0;
	array[(*i) + 1].raw_content = join_to_link_args(array, (*i) + 1, &j);
	if (!array[(*i) + 1].raw_content)
		exit_minishell(input, EXIT_FAILURE);
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
		array[(*i)].formatted_content = ft_strdup(array[(*i) + 1].raw_content);
		if (!array[(*i)].formatted_content)
			exit_minishell(input, EXIT_FAILURE);
		(*i)++;
	}
	(*i) += j + 1;
}
