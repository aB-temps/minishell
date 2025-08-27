/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/27 17:01:18 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "utils.h"

static enum e_bool	execute_block_cmd(t_input *input, t_exec *exec, ssize_t i)
{
	if (!exec->block.cmd)
	{
		if (!create_files_in_block(input, exec, i))
			return (FALSE);
	}
	else
	{
		if (exec->block.cmd->is_builtin)
			handle_builtin(input, exec, &exec->pid_child[i], i);
		else if (!exec_cmd(input, exec, &exec->pid_child[i], i))
			return (FALSE);
	}
	return (TRUE);
}

static enum e_bool	set_blocks(t_exec *exec, t_input *input)
{
	size_t	i;
	ssize_t	index_token;

	index_token = 0;
	i = 0;
	while (i < exec->block_qty)
	{
		if (i != exec->block_qty - 1)
		{
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (FALSE);
		}
		if (!init_block_cmd(input, exec, &exec->block.cmd, &index_token))
			return (FALSE);
		if (!execute_block_cmd(input, exec, i))
		{
			free_cmd(&exec->block.cmd);
			return (FALSE);
		}
		free_cmd(&exec->block.cmd);
		close_and_swap(exec->pipe_fds);
		i++;
	}
	close_fd_exec(input, exec);
	return (TRUE);
}

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	setup_signals_command();
	if (!init_exec(&exec, input))
		exit_minishell(input, NULL, EXIT_FAILURE);
	if (!set_blocks(exec, input))
		exit_minishell(input, exec, 1);
	wait_child(exec, &input->last_exit_status);
	setup_signals_interactive();
	free_and_close_exec(input, exec);
}
