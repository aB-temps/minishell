/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:27:40 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/01 20:42:59 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"

void	close_fd_exec(t_input *input, t_exec *exec)
{
	close_all_hd(input);
	if (exec)
	{
		if (exec->pipe_fds)
		{
			safe_close(&exec->pipe_fds->fd1[0]);
			safe_close(&exec->pipe_fds->fd1[1]);
			safe_close(&exec->pipe_fds->fd2[0]);
			safe_close(&exec->pipe_fds->fd2[1]);
		}
		safe_close(&exec->block.io_fds[0]);
		safe_close(&exec->block.io_fds[1]);
	}
}
