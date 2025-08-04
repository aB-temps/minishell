/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:33:44 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 21:27:31 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_exec(t_exec *exec, const char *stage)
{
	size_t	i;

	// const char	*type[4] = {"NO_TYPE", "CMD_REDIR", "CMD_NOREDIR",
	// 		"REDIR_NOCMD"};
	i = 0;
	printf(BOLD "\n========================\n%s\n" R_ALL, stage);
	printf(DIM "block_qty: %zu\n" R_ALL, exec->block_qty);
	while (i < exec->block_qty)
	{
		printf(BOLD "------------\n" R_ALL);
		printf(BOLD "BLOCK[%zu]\n" R_ALL, i);
		// if (exec->pid_child)
		// 	printf(DIM "pid:%d\n\n" R_ALL, exec->pid_child[i]);
		// if (exec->block[i].type)
		// {
		// 	printf(UNDL "Type:%s %s%s\n" R_ALL, R_ALL, BOLD,
		// 		type[exec->block[i].type]);
		// }
		if (exec->block[i].cmd)
		{
			printf(UNDL "Path:%s '%s'\n", R_ALL, exec->block[i].cmd->cmd_path);
			if (exec->block[i].cmd->cmd_args)
			{
				printf(UNDL "Args:\n" R_ALL);
				print_tab(exec->block[i].cmd->cmd_args);
			}
			printf(UNDL "Builtin:" R_ALL);
			exec->block[i].cmd->is_builtin == true ? printf(BOLD " Yes\n" R_ALL) : printf(BOLD " No\n" R_ALL);
		}
		printf(UNDL "Redir_IN:%s%s %d\n" R_ALL, R_ALL, BOLD,
			((int *)exec->block[i].io_fds)[0]);
		printf(UNDL "Redir_OUT:%s%s %d\n" R_ALL, R_ALL, BOLD,
			((int *)exec->block[i].io_fds)[1]);
		printf(BOLD "------------\n\n" R_ALL);
		i++;
	}
	printf(BOLD "========================\n\n" R_ALL);
}
