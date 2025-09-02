/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:49:29 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/02 19:55:03 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "wait.h"
#include <unistd.h>

static void	handle_no_pid(void)
{
	if (g_sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_sig = 0;
}

static void	handle_pid(int status, int *exit_status, int *last_block_has_pid)
{
	if (WIFSIGNALED(status))
	{
		*exit_status = 128 + WTERMSIG(status);
		if (g_sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	*last_block_has_pid = 1;
}

void	wait_child(t_exec *exec, int *exit_status)
{
	size_t	i;
	int		status;
	int		last_block_has_pid;

	i = 0;
	last_block_has_pid = 0;
	while (i < exec->block_qty)
	{
		if (exec->pid_child[i] > 0)
		{
			waitpid(exec->pid_child[i], &status, 0);
			if (i == exec->block_qty - 1)
				handle_pid(status, exit_status, &last_block_has_pid);
			else
				last_block_has_pid = 1;
		}
		i++;
	}
	if (!last_block_has_pid)
	{
		printf("COU\n");
		*exit_status = 0;
		if (g_sig != 0)
			handle_no_pid();
	}
	g_sig = 0;
}
