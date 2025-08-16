/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:49:29 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 21:26:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "wait.h"

void	wait_child(t_exec *exec, int *exit_status)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < exec->block_qty)
	{
		if (exec->pid_child[i] >= 0)
		{
			waitpid(exec->pid_child[i], &status, 0);
			if (WIFSIGNALED(status))
				*exit_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status) && i == exec->block_qty - 1)
				*exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}
