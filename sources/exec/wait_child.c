/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:49:29 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/31 05:44:21 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "wait.h"

void	wait_child(t_exec *exec, int *exit_status)
{
	size_t	i;
	int		status;
	int		last_has_pid;

	i = 0;
	last_has_pid = 0;
	while (i < exec->block_qty)
	{
		if (exec->pid_child[i] > 0)
		{
			waitpid(exec->pid_child[i], &status, 0);
			if (WIFSIGNALED(status))
				*exit_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status) && i == exec->block_qty - 1)
				*exit_status = WEXITSTATUS(status);
			if (i == exec->block_qty - 1)
				last_has_pid = 1;
		}
		i++;
	}
	if (!last_has_pid)
		*exit_status = 0;
}
