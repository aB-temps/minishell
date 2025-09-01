/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:53:10 by enzo              #+#    #+#             */
/*   Updated: 2025/09/01 20:53:14 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>

static void	exit_builtins_redir(t_minishell *minishell, int old_stdin,
		int old_stdout)
{
	safe_close(&old_stdin);
	safe_close(&old_stdout);
	exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
}

static void	error_occured(t_input *input, t_exec *exec, char *error_msg)
{
	perror(error_msg);
	exit_minishell(input, exec, errno);
}

int	apply_redirections_builtin(t_minishell *minishell, int *old_stdout,
		int *old_stdin)
{
	*old_stdout = dup(STDOUT_FILENO);
	if (*old_stdout == -1)
		exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
	*old_stdin = dup(STDIN_FILENO);
	if (*old_stdin == -1)
		exit_builtins_redir(minishell, *old_stdin, *old_stdout);
	if (minishell->exec->block.io_fds[0] != -1)
	{
		if (dup2(minishell->exec->block.io_fds[0], STDIN_FILENO) == -1)
			exit_builtins_redir(minishell, *old_stdin, *old_stdout);
	}
	if (minishell->exec->block.io_fds[1] != -1)
	{
		if (dup2(minishell->exec->block.io_fds[1], STDOUT_FILENO) == -1)
			exit_builtins_redir(minishell, *old_stdin, *old_stdout);
	}
	return (0);
}

void	restore_redirections_builtin(t_input *input, t_exec *exec,
		int old_stdout, int old_stdin)
{
	if (old_stdout != -1)
	{
		if (dup2(old_stdout, STDOUT_FILENO) == -1)
		{
			safe_close(&old_stdin);
			safe_close(&old_stdout);
			error_occured(input, exec, "dup2");
		}
		safe_close(&old_stdout);
	}
	if (old_stdin != -1)
	{
		if (dup2(old_stdin, STDIN_FILENO) == -1)
		{
			safe_close(&old_stdout);
			safe_close(&old_stdin);
			error_occured(input, exec, "dup2");
		}
		safe_close(&old_stdin);
	}
}

void	prepare_redir(t_input *input, t_exec *exec, size_t i)
{
	if (exec->block.io_fds[0] != -1)
	{
		if (dup2(exec->block.io_fds[0], STDIN_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	else if (i > 0 && exec->pid_child[i - 1] > 0)
	{
		if (dup2(exec->pipe_fds->fd1[0], STDIN_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	if (exec->block.io_fds[1] != -1)
	{
		if (dup2(exec->block.io_fds[1], STDOUT_FILENO) == -1)
			error_occured(input, exec, "DEBUG");
	}
	else if (i < exec->block_qty - 1)
	{
		if (dup2(exec->pipe_fds->fd2[1], STDOUT_FILENO) == -1)
			error_occured(input, exec, "dup2");
	}
	close_fd_exec(input, exec);
}
