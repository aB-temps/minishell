/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/29 09:07:06 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static enum e_bool	setup_block_cmd(t_token token, t_cmd *cmd)
{
	cmd->cmd_path = NULL;
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	return (TRUE);
}

enum e_bool	init_block_cmd(t_input *input, t_cmd **cmd, ssize_t *i)
{
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	while (*i < input->token_qty)
	{
		if (token_array[*i].type == COMMAND)
		{
			*cmd = malloc(sizeof(t_cmd));
			if (!*cmd)
				return (FALSE);
			setup_block_cmd(token_array[*i], *cmd);
			break ;
		}
		++(*i);
	}
	if (!cmd)
		return (FALSE);
	++(*i);
	return (TRUE);
}
