/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/27 06:22:22 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "input.h"
#include <stdio.h>

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd,
			"env") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	execute_builtin(char **cmd, t_input *input, t_exec *exec)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, input);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, input);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, input);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(input->env->array);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, input, exec);
}

static void	restore_redirections_builtin(int old_stdout, int old_stdint)
{
	if (old_stdout != -1)
	{
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
	}
	if (old_stdint != -1)
	{
		dup2(old_stdint, STDIN_FILENO);
		close(old_stdint);
	}
}

int	is_builtin(t_token current_token, t_input *input, t_exec *exec, int i)
{
	char	**cmd;
	int		pid;
	int		old_stdout;
	int		old_stdint;

	cmd = ((char **)current_token.formatted_content);
	if (check_builtin(cmd[0]) == 0)
		return (0);
	if (exec->cmd_count > 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
		{
			prepare_pipe(exec, i);
			execute_builtin(cmd, input, exec);
			exit(free_child(exec, input, 0));
		}
		return (pid);
	}
	else
	{
		old_stdout = -1;
		old_stdint = -1;
		apply_redirections_builtin(input, &old_stdout, &old_stdint);
		execute_builtin(cmd, input, exec);
		restore_redirections_builtin(old_stdout, old_stdint);
		return (1);
	}
}
