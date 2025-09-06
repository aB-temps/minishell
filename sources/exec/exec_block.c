/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:43:07 by enzo              #+#    #+#             */
/*   Updated: 2025/09/06 19:30:56 by enzo             ###   ########.fr       */
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
	block_idx = i;
	ret = init_block_cmd(input, exec, &exec->block.cmd, &block_idx);
	if (ret == -1)
		return (1);
	if (!create_files_in_block(input, exec, i))
	{
		ret = 0;
		input->last_exit_status = 1;
	}
	if (ret == 0)
	{
		if (input->last_exit_status != 1)
			input->last_exit_status = 0;
		close_and_swap(exec->pipe_fds);
		return (0);
	}
	if (!handle_block_with_cmd(input, exec, i))
		return (1);
	return (0);
}

enum e_bool	set_blocks(t_exec *exec, t_input *input)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < exec->block_qty)
	{
		if (i != exec->block_qty - 1)
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (FALSE);
		ret = handle_block(exec, input, i);
		if (ret == 1)
			return (FALSE);
		i++;
	}
	close_fd_exec(input, exec);
	return (TRUE);
}
