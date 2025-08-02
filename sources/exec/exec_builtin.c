/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/02 17:50:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "input.h"
#include <stdio.h>

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	execute_builtin(char **cmd, t_minishell *minishell)
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
		minishell->input->last_exit_status
			= ft_env(minishell->input->env->array);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, minishell);
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

static int	handle_multiple_cmd(t_minishell *minishell, int i, char **cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		prepare_pipe(minishell->exec, i);
		execute_builtin(cmd, minishell);
		exit_minishell(minishell->input, minishell->exec, EXIT_SUCCESS);
	}
	return (pid);
}

int	is_builtin(t_token current_token, t_input *input, t_exec *exec, int i)
{
	char		**cmd;
	int			old_stdout;
	int			old_stdin;
	t_minishell	minishell;

	minishell.input = input;
	minishell.exec = exec;
	cmd = ((char **)current_token.formatted_content);
	if (check_builtin(cmd[0]) == 0)
		return (0);
	if (exec->cmd_count > 1)
		return (handle_multiple_cmd(&minishell, i, cmd));
	else
	{
		old_stdout = -1;
		old_stdin = -1;
		apply_redirections_builtin(input, &old_stdout, &old_stdin);
		execute_builtin(cmd, &minishell);
		restore_redirections_builtin(old_stdout, old_stdin);
		return (1);
	}
}
