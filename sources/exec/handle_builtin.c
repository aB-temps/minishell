/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:03:13 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/16 20:05:10 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

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
		minishell->input->last_exit_status = \
		ft_env(minishell->input->env->array);
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
		return (free_and_close_exec(&exec));
	if (*pid_child == 0)
	{
		if (!create_files_in_block(input, exec, i))
			exit_minishell(input, exec, 1);
		prepare_redir(input, exec, i);
		exec_builtin(exec->block.cmd->cmd_args, &minishell);
		exit_minishell(input, exec, minishell.input->last_exit_status);
	}
	return (minishell.exec->return_error);
}

static int	handle_builtin_single(t_input *input, t_exec *exec, int i)
{
	int			old_stdout;
	int			old_stdin;
	t_minishell	minishell;

	minishell.input = input;
	minishell.exec = exec;
	old_stdout = -1;
	old_stdin = -1;
	apply_redirections_builtin(&minishell, &old_stdout, &old_stdin, i);
	exec_builtin(exec->block.cmd->cmd_args, &minishell);
	restore_redirections_builtin(old_stdout, old_stdin);
	return (minishell.exec->return_error);
}

int	handle_builtin(t_input *input, t_exec *exec, int *pid_child, int i)
{
	if (exec->block_qty > 1)
		return (handle_builtin_pipeline(input, exec, pid_child, i));
	else
		return (handle_builtin_single(input, exec, i));
}
