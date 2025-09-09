/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:43:07 by enzo              #+#    #+#             */
/*   Updated: 2025/09/08 12:49:29 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static int	handle_block(t_exec *exec, t_input *input, size_t i)
{
	int		ret;
	ssize_t	block_idx;

	cleanup_io_fds(exec);
	free_cmd(&exec->block.cmd);
	block_idx = (ssize_t)i;
	ret = init_block_cmd(input, exec, &exec->block.cmd, &block_idx);
	if (ret == -1)
		return (1);
	if (!create_files_in_block(input, exec, (ssize_t)i))
	{
		ret = 0;
		input->last_exit_status = 1;
	}
	else
		input->last_exit_status = 0;
	if (ret == 0)
	{
		if (input->last_exit_status != 1)
			input->last_exit_status = 0;
		close_and_swap(exec->pipe_fds);
		return (0);
	}
	return (handle_block_with_cmd(input, exec, i));
}

bool	set_blocks(t_exec *exec, t_input *input)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < exec->block_qty)
	{
		if (i != exec->block_qty - 1)
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (false);
		ret = handle_block(exec, input, i);
		if (ret == 1)
			return (false);
		i++;
	}
	close_fd_exec(input, exec);
	return (true);
}
