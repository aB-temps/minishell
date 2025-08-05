/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:33:44 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 18:03:26 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_exec(t_exec *exec, const char *stage)
{
	size_t	i;

	// const char	*type[4] = {"NO_TYPE", "CMD_REDIR", "CMD_NOREDIR",
	// 		"REDIR_NOCMD"};
	i = 0;
	dprintf(STDERR_FILENO, BOLD "\n========================\n%s\n" R_ALL,
		stage);
	dprintf(STDERR_FILENO, DIM "block_qty: %zu\n" R_ALL, exec->block_qty);
	while (i < exec->block_qty)
	{
		dprintf(STDERR_FILENO, BOLD "------------\n" R_ALL);
		dprintf(STDERR_FILENO, BOLD "BLOCK[%zu]\n" R_ALL, i);
		// if (exec->pid_child)
		// 	dprintf(STDERR_FILENO,DIM "pid:%d\n\n" R_ALL, exec->pid_child[i]);
		// if (exec->block[i].type)
		// {
		// 	dprintf(STDERR_FILENO,UNDL "Type:%s %s%s\n" R_ALL, R_ALL, BOLD,
		// 		type[exec->block[i].type]);
		// }
		if (exec->block.cmd)
		{
			dprintf(STDERR_FILENO, UNDL "Path:%s '%s'\n", R_ALL,
				exec->block.cmd->cmd_path);
			if (exec->block.cmd->cmd_args)
			{
				dprintf(STDERR_FILENO, UNDL "Args:\n" R_ALL);
				print_tab(exec->block.cmd->cmd_args);
			}
			dprintf(STDERR_FILENO, UNDL "Builtin:" R_ALL);
			exec->block.cmd->is_builtin == true ? dprintf(STDERR_FILENO,
					BOLD " Yes\n" R_ALL) : dprintf(STDERR_FILENO,
					BOLD " No\n" R_ALL);
		}
		dprintf(STDERR_FILENO, UNDL "Redir_IN:%s%s %d\n" R_ALL, R_ALL, BOLD,
			((int *)exec->block.io_fds)[0]);
		dprintf(STDERR_FILENO, UNDL "Redir_OUT:%s%s %d\n" R_ALL, R_ALL, BOLD,
			((int *)exec->block.io_fds)[1]);
		dprintf(STDERR_FILENO, BOLD "------------\n\n" R_ALL);
		i++;
	}
	printf(BOLD "========================\n\n" R_ALL);
}
