/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 01:09:47 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "input.h"
#include "utils.h"

static bool	setup_block_cmd(t_input *input, t_exec *exec, t_token token,
		t_cmd *cmd)
{
	cmd->cmd_path = NULL;
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	if (!cmd->is_builtin)
		cmd->cmd_path = get_cmd_path(input, exec, cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
	return (true);
}

bool	init_block_cmd(t_input *input, t_exec *exec, t_cmd **cmd, ssize_t *i)
{
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	while (*i < input->token_qty)
	{
		if (token_array[*i].type == COMMAND)
		{
			// printf("INSIDE[%zu] = '%s'\n", *i,
			// 	((char **)token_array[*i].formatted_content)[0]);
			*cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				return (false);
			setup_block_cmd(input, exec, token_array[*i], *cmd);
			break ;
		}
		++(*i);
	}
	++(*i);
	return (true);
}
