/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:16:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/18 05:07:21 by enchevri         ###   ########lyon.fr   */
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

enum e_bool	free_and_close_exec(t_exec **exec)
{
	if (exec && *exec)
	{
		close_fd_exec(*exec);
		if ((*exec)->pid_child)
			free((*exec)->pid_child);
		if ((*exec)->pipe_fds)
			free((*exec)->pipe_fds);
		free_cmd(&(*exec)->block.cmd);
		free(*exec);
		*exec = NULL;
	}
	return (FALSE);
}
