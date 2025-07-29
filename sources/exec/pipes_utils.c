/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:55 by enzo              #+#    #+#             */
/*   Updated: 2025/07/29 07:58:15 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

static void	first_cmd(t_exec *exec, int fd_infile)
{
	if (fd_infile == -1)
	{
		if (dup2(exec->fd->fd2[1], STDOUT_FILENO) == -1)
			error_occured(exec, "dup2");
		close_all(exec);
		return ;
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		error_occured(exec, "dup2");
	if (dup2(exec->fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(exec, "dup2");
	close_all(exec);
}

static void	middle_cmd(t_exec *exec)
{
	if (dup2(exec->fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(exec, "dup2");
	if (dup2(exec->fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(exec, "dup2");
	close_all(exec);
}

static void	last_cmd(t_exec *exec, int fd_outfile)
{
	if (fd_outfile == -1)
	{
		if (dup2(exec->fd->fd1[0], STDIN_FILENO) == -1)
			error_occured(exec, "dup2");
		close_all(exec);
		return ;
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		error_occured(exec, "dup2");
	if (dup2(exec->fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(exec, "dup2");
	close_all(exec);
}

int	close_all(t_exec *exec)
{
	if (exec->fd->fd1[0] != -1)
		close(exec->fd->fd1[0]);
	if (exec->fd->fd1[1] != -1)
		close(exec->fd->fd1[1]);
	if (exec->fd->fd2[0] != -1)
		close(exec->fd->fd2[0]);
	if (exec->fd->fd2[1] != -1)
		close(exec->fd->fd2[1]);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
	if (exec->fd_outfile != -1)
		close(exec->fd_outfile);
	return (1);
}

void	prepare_pipe(t_exec *exec, int i)
{
	if (exec->cmd_count == 1)
	{
		if (exec->fd_infile != -1)
		{
			if (dup2(exec->fd_infile, STDIN_FILENO) == -1)
				error_occured(exec, "dup2");
		}
		if (exec->fd_outfile != -1)
		{
			if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
				error_occured(exec, "dup2");
		}
		return ;
	}
	if (i == 0)
		first_cmd(exec, exec->fd_infile);
	else if (i == exec->cmd_count - 1)
		last_cmd(exec, exec->fd_outfile);
	else
		middle_cmd(exec);
}
