/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:55:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/04 01:41:51 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "exec.h"
#include "signals.h"
#include "text_formatting.h"
#include "utils.h"
#include <sys/stat.h>

void	handle_cmd_not_found(t_input *input, t_exec *exec)
{
	char	*error_msg;
	char	*temp;

	temp = ft_strjoin("minishell: ", exec->block.cmd->cmd_args[0]);
	error_msg = ft_strjoin(temp, ": command not found\n");
	if (temp)
		free(temp);
	if (!error_msg)
		exit_minishell(input, exec, 1);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	exit_minishell(input, exec, 127);
}

void	handle_is_directory(t_input *input, t_exec *exec)
{
	char	*error_msg;
	char	*temp;

	temp = ft_strjoin("minishell: ", exec->block.cmd->cmd_args[0]);
	error_msg = ft_strjoin(temp, ": Is a directory\n");
	if (temp)
		free(temp);
	if (!error_msg)
		exit_minishell(input, exec, 1);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	exit_minishell(input, exec, 126);
}

static void	handle_execve_error(t_input *input, t_exec *exec)
{
	if (ft_strchr(exec->block.cmd->cmd_path, '/'))
		perror(exec->block.cmd->cmd_args[0]);
	else
		handle_cmd_not_found(input, exec);
}

static void	handle_child_process(t_input *input, t_exec *exec, size_t i)
{
	struct stat	buf;
	int			exit_code;

	set_sig_for_child();
	if (!exec->block.cmd->cmd_path)
		handle_cmd_not_found(input, exec);
	if (stat(exec->block.cmd->cmd_path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			handle_is_directory(input, exec);
	}
	prepare_redir(input, exec, i);
	execve(exec->block.cmd->cmd_path, exec->block.cmd->cmd_args,
		input->env->array);
	exit_code = 126;
	if (exec->return_error)
		exit_code = exec->return_error;
	handle_execve_error(input, exec);
	exit_minishell(input, exec, exit_code);
}

enum e_bool	exec_cmd(t_input *input, t_exec *exec, int *pid, size_t i)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (*pid == 0)
		handle_child_process(input, exec, i);
	return (TRUE);
}
