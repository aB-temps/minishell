/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:55 by enzo              #+#    #+#             */
/*   Updated: 2025/07/24 11:19:44 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

void	error_occured(t_exec *exec, t_fd *fd, char *error_msg)
{
	if (error_msg != NULL)
		perror(error_msg);
	close_all(exec, fd);
	exit(1);
}

void	first_cmd(t_exec *exec, t_fd *fd, int fd_infile)
{
	if (fd_infile == -1)
	{
		if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
			error_occured(exec, fd, "dup2");
		close_all(exec, fd);
		return ;
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	close_all(exec, fd);
}

void	middle_cmd(t_exec *exec, t_fd *fd)
{
	if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	close_all(exec, fd);
}

void	last_cmd(t_exec *exec, t_fd *fd, int fd_outfile)
{
	if (fd_outfile == -1)
	{
		if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
			error_occured(exec, fd, "dup2");
		close_all(exec, fd);
		return ;
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(exec, fd, "dup2");
	close_all(exec, fd);
}

void	close_all(t_exec *exec, t_fd *fd)
{
	if (fd->fd1[0] != -1)
		close(fd->fd1[0]);
	if (fd->fd1[1] != -1)
		close(fd->fd1[1]);
	if (fd->fd2[0] != -1)
		close(fd->fd2[0]);
	if (fd->fd2[1] != -1)
		close(fd->fd2[1]);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
	if (exec->fd_outfile != -1)
		close(exec->fd_outfile);
}

void	close_and_swap_pipes(t_exec *exec, t_fd *fd)
{
	close_all(exec, fd);
	fd->fd1[0] = fd->fd2[0];
	fd->fd1[1] = fd->fd2[1];
}

void	prepare_pipe(t_exec *exec, t_fd *fd, int i)
{
	if (exec->cmd_count == 1)
	{
		if (exec->fd_infile != -1)
		{
			if (dup2(exec->fd_infile, STDIN_FILENO) == -1)
				error_occured(exec, fd, "dup2");
		}
		if (exec->fd_outfile != -1)
		{
			if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
				error_occured(exec, fd, "dup2");
		}
		return ;
	}
	if (i == 0)
		first_cmd(exec, fd, exec->fd_infile);
	else if (i == exec->cmd_count - 1)
		last_cmd(exec, fd, exec->fd_outfile);
	else
		middle_cmd(exec, fd);
}
