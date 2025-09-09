/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:35:58 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:35:27 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static void	*joinback_args(t_token *array, ssize_t *k, size_t *arg_qty)
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
		array[*k].link_to_next = 0;
		(*k)++;
		(*arg_qty)--;
	}
	return (content);
}

static char	*fill_args_array(t_token *array, ssize_t *k, size_t *arg_qty)
{
	char	*content;

	content = (void *)0;
	if (array[*k].link_to_next)
		content = joinback_args(array, k, arg_qty);
	else if (array[*k].type == ENV_VAR)
		content = ft_strdup(array[*k].formatted_content);
	else if (array[*k].raw_content)
		content = ft_strdup(array[*k].raw_content);
	return (content);
}

static char	**command_args_to_array(t_input *input, t_token *array, ssize_t *i,
		size_t arg_qty)
{
	char	**args_array;
	size_t	j;
	ssize_t	k;

	j = 0;
	k = *i;
	args_array = ft_calloc(arg_qty + 1, sizeof(char *));
	if (!args_array)
		exit_parsing(input, EXIT_FAILURE);
	while (j < arg_qty)
	{
		if (array[k].type >= ARG)
		{
			args_array[j] = fill_args_array(array, &k, &arg_qty);
			if (!args_array[j])
			{
				free_tab_return_null(args_array);
				exit_parsing(input, EXIT_FAILURE);
			}
			j++;
		}
		k++;
	}
	args_array[arg_qty] = (void *)0;
	return (args_array);
}

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	char	**tmp;
	size_t	arg_qty;

	tmp = (char **)array[*i].formatted_content;
	arg_qty = count_command_args(input, array, i);
	array[*i].formatted_content = command_args_to_array(input, array, i,
			arg_qty);
	free(tmp);
	if (!array[*i].formatted_content)
		exit_parsing(input, EXIT_FAILURE);
	array[*i].type = COMMAND;
	(*i) += arg_qty + 1;
}
