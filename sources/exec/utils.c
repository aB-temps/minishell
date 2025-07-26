/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:57 by enzo              #+#    #+#             */
/*   Updated: 2025/07/24 16:39:50 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "input.h"
#include <fcntl.h>

void	exit_exec(t_input *input, t_exec *exec)
{
	close_all(exec);
	free(exec->pid_child);
	free(exec->fd);
	exit_minishell(input, input->last_exit_status);
}

char	*get_cmd_by_index(t_input *input, t_token *tokens_array, int index)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = 0;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		if (cmd_count - 1 == index)
			return (((char **)tokens_array[i].formatted_content)[0]);
		i++;
	}
	return (NULL);
}

int	count_cmd(t_input *input)
{
	int		i;
	int		cmd_count;
	t_token	*tokens_array;

	i = 0;
	cmd_count = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		i++;
	}
	return (cmd_count);
}
