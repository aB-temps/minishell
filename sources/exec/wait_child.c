/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:49:29 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/02 17:13:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "wait.h"
#include <unistd.h>

void	handle_no_pid(void)
{
	if (g_sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_sig = 0;
}

int	handle_pid(t_exec *exec, int status, int *exit_status, size_t i)
{
	if (WIFSIGNALED(status))
	{
		*exit_status = 128 + WTERMSIG(status);
		if (g_sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (WIFEXITED(status) && i == exec->block_qty - 1)
	{
		*exit_status = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

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
			if (i == exec->block_qty - 1)
				if (handle_pid(exec, status, exit_status, i) == 0)
					last_has_pid = 1;
		}
		i++;
	}
	if (!last_has_pid)
	{
		*exit_status = 0;
		if (g_sig != 0)
			handle_no_pid();
	}
}
