/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 01:10:19 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "utils.h"

static bool	execute_block_cmd(t_input *input, t_exec *exec, ssize_t i)
{
	if (exec->block.cmd->is_builtin)
	{
		printf("builtin\n");
		// exec_builtin(input, block, &exec->pid_child[i], i);
	}
	else if (!exec_cmd(input, exec, &exec->pid_child[i], i))
		return (false);
	return (true);
}

static bool	set_blocks(t_exec *exec, t_input *input)
{
	t_token	*array;
	size_t	i;
	ssize_t	index_token;

	index_token = 0;
	i = 0;
	array = (t_token *)input->v_tokens->array;
	while (i < exec->block_qty)
	{
		// printf("BEFORE %zu\n", index_token);
		init_block_cmd(input, exec, &exec->block.cmd, &index_token);
		// printf("AFTER %zu\n", index_token);
		if (i != exec->block_qty - 1)
		{
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (-1);
		}
		if (!execute_block_cmd(input, exec, i))
			return (false);
		free_cmd(&exec->block.cmd);
		if (i < exec->block_qty - 1)
			close_and_swap(exec->pipe_fds);
		i++;
	}
	wait_child(exec, &input->last_exit_status);
	return (true);
}

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	if (!init_exec(&exec, input))
		exit_minishell(input, NULL, EXIT_FAILURE);
	if (!set_blocks(exec, input))
		exit_minishell(input, exec, 1);
	free_and_close_exec(&exec);
}
