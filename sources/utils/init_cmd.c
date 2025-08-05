/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 21:14:20 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "input.h"
#include "utils.h"

static bool	setup_block_cmd(t_input *input, t_token token, t_cmd *cmd)
{
	cmd->cmd_path = NULL;
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	if (!cmd->is_builtin)
		cmd->cmd_path = get_cmd_path(input, cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
	return (true);
}

bool	init_cmd(t_input *input, t_cmd **cmd, ssize_t *i)
{
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	while (*i < input->token_qty)
	{
		if (token_array[*i].type == COMMAND)
		{
			*cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				return (false);
			setup_block_cmd(input, token_array[*i], *cmd);
		}
		++(*i);
	}
	return (true);
}
