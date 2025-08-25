/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:27:40 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/19 18:03:19 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"

void	close_fd_exec(t_input *input, t_exec *exec)
{
	close_all_hd(input);
	safe_close(exec->pipe_fds->fd1[0]);
	safe_close(exec->pipe_fds->fd1[1]);
	safe_close(exec->pipe_fds->fd2[0]);
	safe_close(exec->pipe_fds->fd2[1]);
	safe_close(exec->block.io_fds[0]);
	safe_close(exec->block.io_fds[1]);
}
