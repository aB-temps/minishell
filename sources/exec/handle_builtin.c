/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:03:13 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/08 18:30:36 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static void	apply_redirections_builtin(t_minishell *minishell, int *old_stdout,
		int *old_stdin, int i)
{
	*old_stdout = dup(STDOUT_FILENO);
	*old_stdin = dup(STDIN_FILENO);
	if (!create_files_in_block(minishell->input, minishell->exec, i))
		return ;
	if (minishell->exec->block.io_fds[0] != -1)
		dup2(minishell->exec->block.io_fds[0], STDIN_FILENO);
	if (minishell->exec->block.io_fds[1] != -1)
		dup2(minishell->exec->block.io_fds[1], STDOUT_FILENO);
}

static void	restore_redirections_builtin(int old_stdout, int old_stdin)
{
	if (old_stdout != -1)
	{
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
	}
	if (old_stdin != -1)
	{
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdin);
	}
}

static void	exec_builtin(char **cmd, t_minishell *minishell)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		minishell->input->last_exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		minishell->input->last_exit_status = ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		minishell->input->last_exit_status = ft_cd(cmd, minishell);
	else if (ft_strcmp(cmd[0], "export") == 0)
		minishell->input->last_exit_status = ft_export(cmd, minishell);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		minishell->input->last_exit_status = ft_unset(cmd, minishell);
	else if (ft_strcmp(cmd[0], "env") == 0)
		minishell->input->last_exit_status = ft_env(minishell->input->env->array);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, minishell);
}

int	handle_builtin(t_input *input, t_exec *exec, int *pid_child, int i)
{
	int old_stdout;
	int old_stdin;
	t_minishell minishell;

	minishell.input = input;
	minishell.exec = exec;

	if (exec->block_qty > 1)
	{
		prepare_redir(input, exec, i);

		*pid_child = fork();
		if (*pid_child == -1)
		{
			free_and_close_exec(&exec);
			perror("fork");
			return (FALSE);
		}
		if (*pid_child == 0)
		{
			exec_builtin(exec->block.cmd->cmd_args, &minishell);
			exit(minishell.exec->return_error);
		}
		return (minishell.exec->return_error);
	}
	else
	{
		old_stdout = -1;
		old_stdin = -1;
		apply_redirections_builtin(&minishell, &old_stdout, &old_stdin, i);
		exec_builtin(exec->block.cmd->cmd_args, &minishell);
		restore_redirections_builtin(old_stdout, old_stdin);
		return (minishell.exec->return_error);
	}
}
