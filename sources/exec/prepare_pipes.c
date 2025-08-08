/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:18:36 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/08 13:41:02 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>

static void	error_occured(t_input *input, t_exec *exec, char *error_msg)
{
	perror(error_msg);
	exit_minishell(input, exec, errno);
}

void	prepare_pipes(t_input *input, t_exec *exec, size_t i)
{
	if (exec->block.io_fds[0] != -1)
	{
		if (dup2(exec->block.io_fds[0], STDIN_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	else if (i > 0)
	{
		if (dup2(exec->pipe_fds->fd1[0], STDIN_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	if (exec->block.io_fds[1] != -1)
	{
		if (dup2(exec->block.io_fds[1], STDOUT_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	else if (i < exec->block_qty - 1)
	{
		if (dup2(exec->pipe_fds->fd2[1], STDOUT_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	close_fd_exec(exec);
}
