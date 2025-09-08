/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:16:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:41 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	free_cmd(t_cmd **cmd)
{
	if (cmd && *cmd)
	{
		if ((*cmd)->cmd_path)
		{
			free((*cmd)->cmd_path);
			(*cmd)->cmd_path = NULL;
		}
		(*cmd)->cmd_args = NULL;
		free(*cmd);
		*cmd = NULL;
	}
}

bool	free_and_close_exec(t_input *input, t_exec *exec)
{
	if (exec)
	{
		if (input)
			close_fd_exec(input, exec);
		if (exec->pid_child)
			free(exec->pid_child);
		if (exec->pipe_fds)
			free(exec->pipe_fds);
		free_cmd(&exec->block.cmd);
		free(exec);
	}
	return (false);
}
