/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:45:00 by enzo              #+#    #+#             */
/*   Updated: 2025/09/01 23:17:05 by enzo             ###   ########.fr       */
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

enum e_bool	handle_block_no_cmd(t_exec *exec)
{
	close_and_swap(exec->pipe_fds);
	return (TRUE);
}

enum e_bool	handle_block_with_cmd(t_input *input, t_exec *exec, size_t i)
{
	if (exec->block.cmd->is_builtin)
	{
		if (handle_builtin(input, exec, &exec->pid_child[i], i) == -1)
		{
			free_cmd(&exec->block.cmd);
			return (FALSE);
		}
	}
	else if (!exec_cmd(input, exec, &exec->pid_child[i], i))
	{
		free_cmd(&exec->block.cmd);
		return (FALSE);
	}
	free_cmd(&exec->block.cmd);
	close_and_swap(exec->pipe_fds);
	return (TRUE);
}
