/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:43:07 by enzo              #+#    #+#             */
/*   Updated: 2025/09/01 19:22:08 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static enum e_bool	handle_block(t_exec *exec, t_input *input, size_t i)
{
	int		ret;
	ssize_t	block_idx;

	cleanup_io_fds(exec);
	block_idx = i;
	ret = init_block_cmd(input, exec, &exec->block.cmd, &block_idx);
	if (ret == -1)
		exit_minishell(input, exec, EXIT_FAILURE);
	if (!create_files_in_block(input, exec, i))
		return (FALSE);
	if (ret == 0)
		return (handle_block_no_cmd(exec));
	return (handle_block_with_cmd(input, exec, i));
}

enum e_bool	set_blocks(t_exec *exec, t_input *input)
{
	size_t	i;

	i = 0;
	while (i < exec->block_qty)
	{
		if (i != exec->block_qty - 1)
			if (pipe(exec->pipe_fds->fd2) == -1)
				return (FALSE);
		if (!handle_block(exec, input, i))
			return (FALSE);
		i++;
	}
	close_fd_exec(input, exec);
	return (TRUE);
}
