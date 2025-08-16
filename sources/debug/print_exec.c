/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:33:44 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:08 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_exec(t_exec *exec, const char *stage)
{
	dprintf(STDERR_FILENO, BOLD "\n========================\n%s\n" RST, stage);
	dprintf(STDERR_FILENO, DIM "block_qty: %zu\n" RST, exec->block_qty);
	dprintf(STDERR_FILENO, BOLD "------------\n" RST);
	if (exec->block.cmd)
	{
		dprintf(STDERR_FILENO, UNDL "Path:%s '%s'\n", RST,
			exec->block.cmd->cmd_path);
		if (exec->block.cmd->cmd_args)
		{
			dprintf(STDERR_FILENO, UNDL "Args:\n" RST);
			print_tab(exec->block.cmd->cmd_args);
		}
		dprintf(STDERR_FILENO, UNDL "Builtin:" RST);
		exec->block.cmd->is_builtin == TRUE ? dprintf(STDERR_FILENO, BOLD " Yes\n" RST) : dprintf(STDERR_FILENO, BOLD " No\n" RST);
	}
	dprintf(STDERR_FILENO, UNDL "Redir IN:%s%s %d\n" RST, RST, BOLD,
		((int *)exec->block.io_fds)[0]);
	dprintf(STDERR_FILENO, UNDL "Redir OUT:%s%s %d\n" RST, RST, BOLD,
		((int *)exec->block.io_fds)[1]);
	dprintf(STDERR_FILENO, BOLD "------------\n\n" RST);
	dprintf(STDERR_FILENO, BOLD "========================\n\n" RST);
}
