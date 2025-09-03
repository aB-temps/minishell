/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:03:13 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/03 06:39:12 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static void	exec_builtin(char **cmd, t_minishell *minishell)
{
	int	*exit_status;

	exit_status = &minishell->input->last_exit_status;
	if (ft_strcmp(cmd[0], "echo") == 0)
		*exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		*exit_status = ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		*exit_status = ft_cd(cmd, minishell);
	else if (ft_strcmp(cmd[0], "export") == 0)
		*exit_status = ft_export(cmd, minishell);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		*exit_status = ft_unset(cmd, minishell);
	else if (ft_strcmp(cmd[0], "env") == 0)
		*exit_status = ft_env(minishell->input->env->array);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, minishell);
}

static int	handle_builtin_pipeline(t_input *input, t_exec *exec,
		int *pid_child, int i)
{
	t_minishell	minishell;

	minishell.input = input;
	minishell.exec = exec;
	*pid_child = fork();
	if (*pid_child == -1)
	{
		perror("fork");
		return (-1);
	}
	if (*pid_child == 0)
	{
		prepare_redir(input, exec, i);
		exec_builtin(exec->block.cmd->cmd_args, &minishell);
		exit_minishell(input, exec, minishell.input->last_exit_status);
	}
	return (0);
}

static int	handle_builtin_single(t_input *input, t_exec *exec)
{
	int			old_stdout;
	int			old_stdin;
	t_minishell	minishell;

	minishell.input = input;
	minishell.exec = exec;
	old_stdout = -1;
	old_stdin = -1;
	if (ft_strcmp(exec->block.cmd->cmd_args[0], "exit"))
	{
		minishell.input->last_exit_status = apply_redirections_builtin(
				&minishell, &old_stdout, &old_stdin);
		if (minishell.input->last_exit_status)
			return (minishell.input->last_exit_status);
	}
	exec_builtin(exec->block.cmd->cmd_args, &minishell);
	restore_redirections_builtin(input, exec, old_stdout, old_stdin);
	return (minishell.input->last_exit_status);
}

int	handle_builtin(t_input *input, t_exec *exec, int *pid_child, int i)
{
	if (exec->block_qty > 1)
		return (handle_builtin_pipeline(input, exec, pid_child, i));
	else
		return (handle_builtin_single(input, exec));
}
