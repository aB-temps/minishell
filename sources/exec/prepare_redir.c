/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:18:36 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/30 17:47:16 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>

static void	error_occured(t_input *input, t_exec *exec, char *error_msg)
{
	perror(error_msg);
	exit_minishell(input, exec, errno);
}

int	apply_redirections_builtin(t_minishell *minishell, int *old_stdout,
		int *old_stdin, int i)
{
	*old_stdout = dup(STDOUT_FILENO);
	*old_stdin = dup(STDIN_FILENO);
	if (!create_files_in_block(minishell->input, minishell->exec, i))
		return (1);
	if (minishell->exec->block.io_fds[0] != -1)
	{
		if (dup2(minishell->exec->block.io_fds[0], STDIN_FILENO) == -1)
		{
			safe_close(*old_stdin);
			safe_close(*old_stdout);
			exit_minishell(minishell->input, minishell->exec, 1);
		}
	}
	if (minishell->exec->block.io_fds[1] != -1)
	{
		if (dup2(minishell->exec->block.io_fds[1], STDOUT_FILENO) == -1)
		{
			safe_close(*old_stdin);
			safe_close(*old_stdout);
			exit_minishell(minishell->input, minishell->exec, 1);
		}
	}
	return (0);
}

void	restore_redirections_builtin(t_input *input, t_exec *exec,
		int old_stdout, int old_stdin)
{
	if (old_stdout != -1)
	{
		if (dup2(old_stdout, STDOUT_FILENO) == -1)
			error_occured(input, exec, "dup2");
		close(old_stdout);
	}
	if (old_stdin != -1)
	{
		if (dup2(old_stdin, STDIN_FILENO) == -1)
			error_occured(input, exec, "dup2");
		close(old_stdin);
	}
}

void	prepare_redir(t_input *input, t_exec *exec, size_t i)
{
	if (!create_files_in_block(input, exec, i))
		exit_minishell(input, exec, 1);
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
	close_fd_exec(input, exec);
}
