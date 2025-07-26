/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:30:56 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 22:32:33 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static void	*joinback_args(t_token *array, size_t *k, size_t *arg_qty)
{
	char	*content;

	if (array[*k].type == ENV_VAR)
		content = ft_strdup(array[*k].formatted_content);
	else
		content = ft_strdup(array[*k].raw_content);
	if (!content)
		return ((void *)0);
	while (array[*k].link_to_next)
	{
		if (array[*k + 1].type == ENV_VAR)
			content = str_free_to_join(content, array[*k
					+ 1].formatted_content);
		else
			content = str_free_to_join(content, array[*k + 1].raw_content);
		if (!content)
			return ((void *)0);
		(*k)++;
		(*arg_qty)--;
	}
	return (content);
}

static ssize_t	count_command_args(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	j;
	ssize_t	count;

	j = *i;
	count = 0;
	while (j + 1 <= input->token_qty && !(array[j].type >= PIPE
			&& array[j].type <= HEREDOC))
	{
		count++;
		j++;
	}
	return (count + 1);
}

static char	**command_args_to_array(t_input *input, t_token *array, ssize_t *i,
		size_t arg_qty)
{
	char	**args_array;
	char	*content;
	size_t	j;
	size_t	k;

	j = 0;
	k = *i;
	content = (void *)0;
	args_array = malloc(sizeof(char *) * arg_qty + 1);
	if (!args_array)
		exit_minishell(input, EXIT_FAILURE);
	while (j < arg_qty - 1)
	{
		if (array[k].link_to_next)
			content = joinback_args(array, &k, &arg_qty);
		else if (array[k].type == ENV_VAR && array[k].formatted_content)
			content = ft_strdup(array[k].formatted_content);
		else if (array[k].raw_content)
			content = ft_strdup(array[k].raw_content);
		if (!content)
			exit_minishell(input, EXIT_FAILURE);
		args_array[j] = content;
		j++;
		k++;
	}
	args_array[arg_qty - 1] = (void *)0;
	return (args_array);
}

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	arg_qty;

	arg_qty = count_command_args(input, array, i);
	array[*i].formatted_content = command_args_to_array(input, array, i,
			arg_qty);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = COMMAND;
	(*i) += arg_qty - 1;
}
