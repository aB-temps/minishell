/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:45:00 by enzo              #+#    #+#             */
/*   Updated: 2025/09/08 12:44:54 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	cleanup_io_fds(t_exec *exec)
{
	if (exec->block.io_fds[0] != -1)
	{
		safe_close(&exec->block.io_fds[0]);
	}
	if (exec->block.io_fds[1] != -1)
	{
		safe_close(&exec->block.io_fds[1]);
	}
}

int	handle_block_with_cmd(t_input *input, t_exec *exec, size_t i)
{
	int	builtin_result;

	if (exec->block.cmd->is_builtin)
	{
		builtin_result = handle_builtin(input, exec, &exec->pid_child[i], i);
		if (builtin_result == -1)
		{
			free_cmd(&exec->block.cmd);
			return (1);
		}
		if (exec->block_qty == 1)
			input->last_exit_status = builtin_result;
	}
	else if (!exec_cmd(input, exec, &exec->pid_child[i], i))
	{
		free_cmd(&exec->block.cmd);
		return (1);
	}
	free_cmd(&exec->block.cmd);
	close_and_swap(exec->pipe_fds);
	return (0);
}
