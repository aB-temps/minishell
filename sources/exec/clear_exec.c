/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:16:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 18:59:38 by enchevri         ###   ########lyon.fr   */
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
		free(*cmd);
		*cmd = NULL;
	}
}
void	close_all(t_exec *exec)
{
	safe_close(exec->pipe_fds->fd1[0]);
	safe_close(exec->pipe_fds->fd1[1]);
	safe_close(exec->pipe_fds->fd2[0]);
	safe_close(exec->pipe_fds->fd2[1]);
}

void	free_and_close_exec(t_exec **exec)
{
	if (exec && *exec)
	{
		close_all(*exec);
		if ((*exec)->pid_child)
			free((*exec)->pid_child);
		if ((*exec)->pipe_fds)
			free((*exec)->pipe_fds);
		free_cmd(&(*exec)->block.cmd);
		free(*exec);
		*exec = NULL;
	}
}
