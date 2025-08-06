/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:55:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 23:27:56 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "utils.h"

bool	exec_cmd(t_input *input, t_exec *exec, int *pid, size_t i)
{
	*pid = fork();
	if (*pid == -1)
	{
		free_and_close_exec(&exec);
		perror("fork");
		return (false);
	}
	if (*pid == 0)
	{
		set_sig_for_child();
		if (!create_files_in_block(input, exec, i))
			exit_minishell(input, exec, 1);
		if (!exec->block.cmd->cmd_path)
			exit_minishell(input, exec, 126);
		prepare_pipes(input, exec, i);
		execve(exec->block.cmd->cmd_path, exec->block.cmd->cmd_args,
			input->env->array);
		exit_minishell(input, exec, 127);
	}
	return (true);
}
