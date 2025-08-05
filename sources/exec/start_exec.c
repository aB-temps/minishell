/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 17:29:38 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "utils.h"
#include <wait.h>

pid_t	execute_block(t_input *input, t_exec *exec, t_block block, ssize_t i)
{
	pid_t	pid;

	// if (!block.cmd->is_builtin)
	// 	pid = exec_builtin(input, block);
	// else
	pid = exec_cmd(input, exec, block, i);
	return (pid);
}

int	set_blocks(t_exec *exec, t_input *input)
{
	t_token	*array;
	size_t	i;
	int		exit_status;
	// int		status;

	exit_status = 0;
	i = 0;
	array = (t_token *)input->v_tokens->array;
	while (i < exec->block_qty)
	{
		init_cmd(input, &exec->block.cmd);
		if (i != exec->block_qty - 1)
		{
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (-1);
		}
		if (exec->block.cmd)
			exec->pid_child[i] = execute_block(input, exec, exec->block, i);
		free_cmd(exec->block.cmd);
		if (i < exec->block_qty - 1)
			close_and_swap(exec->pipe_fds);
		i++;
	}
	// while (i < exec->block_qty)
	// {
	// 	if (exec->pid_child[i] > 0)
	// 	{
	// 		waitpid(exec->pid_child[i], &status, 0);
	// 		if (i == exec->block_qty - 1) // Dernière commande
	// 			exit_status = WEXITSTATUS(status);
	// 	}
	// 	i++;
	// }
	return (exit_status);
}

void	close_all(t_exec *exec)
{
	safe_close(exec->pipe_fds->fd1[0]);
	safe_close(exec->pipe_fds->fd1[1]);
	safe_close(exec->pipe_fds->fd2[0]);
	safe_close(exec->pipe_fds->fd2[1]);
}

void	free_and_close_exec(t_exec **exec)
{
	if (exec && *exec)
	{
		close_all(*exec);
		if ((*exec)->pid_child)
			free((*exec)->pid_child);
		if ((*exec)->pipe_fds)
			free((*exec)->pipe_fds);
		if ((*exec)->block.cmd)
		{
			if ((*exec)->block.cmd->cmd_path)
				free((*exec)->block.cmd->cmd_path);
		}
		free(*exec);
		*exec = NULL;
	}
}

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	if (!init_exec(&exec, input))
		exit_minishell(input, NULL, EXIT_FAILURE);
	input->last_exit_status = set_blocks(exec, input);
	exit_minishell(input, exec, 0);
}
