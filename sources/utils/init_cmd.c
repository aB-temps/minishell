/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 00:53:37 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"

static bool	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
			|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "exit") == 0)
			return (true);
	}
	return (false);
}

static bool	setup_block_cmd(t_token token, t_block *block, size_t i)
{
	block[i].cmd->cmd_args = (char **)token.formatted_content;
	block[i].cmd->is_builtin = is_builtin(block[i].cmd->cmd_args[0]);
	return (true);
}

bool	init_cmd(t_input *input, t_block *block)
{
	ssize_t	i;
	size_t	j;
	t_token	*token_array;

	i = 0;
	j = 0;
	token_array = (t_token *)input->v_tokens->array;
	while (i < input->token_qty)
	{
		if (token_array[i].type == COMMAND)
		{
			block[j].cmd = malloc(sizeof(t_cmd));
			setup_block_cmd(token_array[i], block, j);
			j++;
		}
		++i;
	}
	return (true);
}
