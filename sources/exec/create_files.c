/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:28:25 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/02 17:48:07 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

int	search_cmd_by_index(t_input *input, t_token *token_array,
		int searched_n_cmd)
{
	int	cmd_count;
	int	i;

	cmd_count = -1;
	i = 0;
	while (i < input->token_qty)
	{
		if (token_array[i].type == COMMAND)
		{
			if (cmd_count == searched_n_cmd)
				break ;
			cmd_count++;
		}
		i++;
	}
	if (i >= input->token_qty)
		return (-1);
	while (i >= 0 && token_array[i].type != PIPE)
		i--;
	return (i);
}

int	create_all_files(t_exec *exec, t_input *input, int cmd_nb)
{
	int		i;
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	i = search_cmd_by_index(input, token_array, cmd_nb);
	if (i != 0)
		i++;
	while (i < input->token_qty)
	{
		if (token_array[i].type == PIPE)
			return (0);
		if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
		{
			if (handle_redir_out(exec, token_array[i]))
				return (2);
		}
		else if (token_array[i].type == REDIR_IN
			|| token_array[i].type == HEREDOC)
		{
			if (handle_redir_in(exec, token_array[i]))
				return (2);
		}
		i++;
	}
	return (0);
}
