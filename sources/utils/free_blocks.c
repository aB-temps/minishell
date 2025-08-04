/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:14:35 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 18:23:25 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->cmd_path)
		{
			free(cmd->cmd_path);
			cmd->cmd_path = NULL;
		}
		if (cmd->cmd_args)
			cmd->cmd_args = free_tab_return_null(cmd->cmd_args);
		free(cmd);
	}
}

void	free_blocks(t_block *block)
{
	int	i;

	i = 0;
	while (&block[i])
	{
		free_cmd(block[i].cmd);
		free(&block[i]);
		++i;
	}
}
