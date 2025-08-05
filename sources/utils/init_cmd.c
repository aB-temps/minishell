/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 13:56:11 by enchevri         ###   ########lyon.fr   */
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

static bool	setup_block_cmd(t_input *input, t_token token, t_cmd *cmd)
{
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	if (!cmd->is_builtin)
		cmd->cmd_path = get_cmd_path(input, cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
	return (true);
}

bool	init_cmd(t_input *input, t_cmd **cmd)
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
			*cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				return (false);
			setup_block_cmd(input, token_array[i], *cmd);
			j++;
		}
		++i;
	}
	return (true);
}
