/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:33:44 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 16:21:37 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	dprintf(STDERR_FILENO, UNDL "Path:%s '%s'\n", RST, cmd->cmd_path);
	if (cmd->cmd_args)
	{
		dprintf(STDERR_FILENO, UNDL "Args:\n" RST);
		print_tab(cmd->cmd_args);
	}
	dprintf(STDERR_FILENO, UNDL "Builtin:" RST);
	if (cmd->is_builtin == true)
		dprintf(STDERR_FILENO, BOLD " Yes\n" RST);
	else
		dprintf(STDERR_FILENO, BOLD " No\n" RST);
}

static void	print_redir(int *io_fds)
{
	dprintf(STDERR_FILENO, UNDL "Redir IN:%s %d\n", RST, io_fds[0]);
	dprintf(STDERR_FILENO, UNDL "Redir OUT:%s %d\n", RST, io_fds[1]);
}

static void	print_pipes(t_pipe_fds *pipe_fds)
{
	dprintf(STDERR_FILENO,
		"Pipe fd1[0] = %d fd1[1] = %d "
		"fd2[0] = %d fd2[1] = %d \n",
		pipe_fds->fd1[0],
		pipe_fds->fd1[1],
		pipe_fds->fd2[0],
		pipe_fds->fd2[1]);
}

void	print_exec(t_exec *exec, const char *stage)
{
	dprintf(STDERR_FILENO, BOLD "\n========================\n%s\n" RST, stage);
	dprintf(STDERR_FILENO, DIM "block_qty: %zu\n" RST, exec->block_qty);
	dprintf(STDERR_FILENO, BOLD "------------\n" RST);
	print_cmd(exec->block.cmd);
	print_redir((int *)exec->block.io_fds);
	dprintf(STDERR_FILENO, BOLD "------------\n\n" RST);
	print_pipes(exec->pipe_fds);
	dprintf(STDERR_FILENO, BOLD "========================\n\n" RST);
}
