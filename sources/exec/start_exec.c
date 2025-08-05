/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 21:14:53 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "utils.h"

static bool	execute_block(t_input *input, t_exec *exec, ssize_t i)
{
	// if (!block.cmd->is_builtin)
	// 	exec_builtin(input, block, &exec->pid_child[i], i);
	// else
	if (!exec_cmd(input, exec, &exec->pid_child[i], i))
		return (false);
	return (true);
}

int	set_blocks(t_exec *exec, t_input *input)
{
	t_token	*array;
	size_t	i;
	int		exit_status;
	ssize_t	index_token;

	index_token = 0;
	exit_status = 0;
	i = 0;
	array = (t_token *)input->v_tokens->array;
	while (i < exec->block_qty)
	{
		init_cmd(input, &exec->block.cmd, &index_token);
		if (i != exec->block_qty - 1)
		{
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (-1);
		}
		if (!execute_block(input, exec, i))
			return (false);
		free_cmd(&exec->block.cmd);
		if (i < exec->block_qty - 1)
			close_and_swap(exec->pipe_fds);
		i++;
	}
	wait_child(exec, &input->last_exit_status);
	return (exit_status);
}

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	if (!init_exec(&exec, input))
		exit_minishell(input, NULL, EXIT_FAILURE);
	input->last_exit_status = set_blocks(exec, input);
	free_and_close_exec(&exec);
}
