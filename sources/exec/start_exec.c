/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 11:00:06 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "utils.h"

pid_t	execute_block(t_input *input, t_exec *exec, t_block block)
{
	pid_t	pid;

	// if (!block.cmd->is_builtin)
	// 	pid = exec_builtin(input, block);
	// else
	pid = exec_cmd(input, exec, block);
	return (pid);
}

int	set_blocks(t_exec *exec, t_input *input)
{
	t_token	*array;
	size_t	i;
	int		exit_status;

	exit_status = 0;
	i = 0;
	array = (t_token *)input->v_tokens->array;
	while (i < exec->block_qty)
	{
		init_cmd(input, exec->block.cmd);
		if (i != exec->block_qty - 1)
		{
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (-1);
		}
		if (exec->block.cmd)
			exec->pid_child[i] = execute_block(input, exec, exec->block);
		free_cmd(exec->block.cmd);
		if (i < exec->block_qty - 1)
			close_and_swap(exec->pipe_fds);
		i++;
	}
	return (exit_status);
}

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	if (!init_exec(&exec, input))
		exit_parsing(input, EXIT_FAILURE);
	input->last_exit_status = set_blocks(exec, input);
	print_exec(exec, "INIT");
}
