/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:18:36 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 21:57:23 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>

static void	error_occured(t_input *input, t_exec *exec, char *error_msg)
{
	perror(error_msg);
	exit_minishell(input, exec, errno);
}

static bool	first_cmd(t_exec *exec, int fd_infile)
{
	if (fd_infile != -1)
	{
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			return (false);
	}
	if (exec->block.io_fds[1] == -1)
	{
		if (dup2(exec->pipe_fds->fd2[1], STDOUT_FILENO) == -1)
			return (false);
	}
	else
	{
		if (dup2(exec->block.io_fds[1], STDOUT_FILENO) == -1)
			return (false);
	}
	return (true);
}

static bool	middle_cmd(t_exec *exec)
{
	if (exec->block.io_fds[0] == -1)
	{
		if (dup2(exec->pipe_fds->fd1[0], STDIN_FILENO) == -1)
			return (false);
	}
	else
	{
		if (dup2(exec->block.io_fds[0], STDIN_FILENO) == -1)
			return (false);
	}
	if (exec->block.io_fds[1] == -1)
	{
		if (dup2(exec->pipe_fds->fd2[1], STDOUT_FILENO) == -1)
			return (false);
	}
	else if (dup2(exec->pipe_fds->fd2[1], STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

static bool	last_cmd(t_exec *exec, int fd_outfile)
{
	if (dup2(exec->pipe_fds->fd1[0], STDIN_FILENO) == -1)
		return (false);
	if (fd_outfile != -1)
	{
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			return (false);
	}
	return (true);
}

void	prepare_pipes(t_input *input, t_exec *exec, size_t i)
{
	if (exec->block_qty == 1)
	{
		if (exec->block.io_fds[0] != -1)
		{
			if (dup2(exec->block.io_fds[0], STDIN_FILENO) == -1)
				error_occured(input, exec, "dup2");
		}
		if (exec->block.io_fds[1] != -1)
		{
			if (dup2(exec->block.io_fds[1], STDOUT_FILENO) == -1)
				error_occured(input, exec, "dup2");
		}
	}
	else if (i == 0)
	{
		if (!first_cmd(exec, exec->block.io_fds[0]))
			error_occured(input, exec, "dup2");
	}
	else if (i == exec->block_qty - 1)
	{
		if (!last_cmd(exec, exec->block.io_fds[1]))
			error_occured(input, exec, "dup2");
	}
	else
	{
		if (!middle_cmd(exec))
			error_occured(input, exec, "dup2");
	}
	close_fd_exec(exec);
}
