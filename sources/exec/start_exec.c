/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/31 05:58:23 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "utils.h"

static enum e_bool	execute_block_cmd(t_input *input, t_exec *exec, ssize_t i)
{
	if (exec->block.cmd->is_builtin)
		handle_builtin(input, exec, &exec->pid_child[i], i);
	else if (!exec_cmd(input, exec, &exec->pid_child[i], i))
		return (FALSE);
	return (TRUE);
}

static enum e_bool	handle_block(t_exec *exec, t_input *input, size_t i,
		ssize_t *index_token)
{
	int	ret;

	ret = init_block_cmd(input, exec, &exec->block.cmd, index_token);
	if (ret == -1)
		exit_minishell(input, exec, EXIT_FAILURE);
	if (ret == 0)
	{
		if (!create_files_in_block(input, exec, i))
			return (FALSE);
		close_and_swap(exec->pipe_fds);
		return (TRUE);
	}
	if (!execute_block_cmd(input, exec, i))
	{
		free_cmd(&exec->block.cmd);
		return (FALSE);
	}
	free_cmd(&exec->block.cmd);
	close_and_swap(exec->pipe_fds);
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
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (FALSE);
		if (!handle_block(exec, input, i, &index_token))
			return (FALSE);
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
