/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/31 04:58:21 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static enum e_bool	setup_block_cmd(t_input *input, t_exec *exec, t_token token,
		t_cmd *cmd)
{
	cmd->cmd_path = NULL;
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	if (cmd->cmd_args[0][0] && !cmd->is_builtin)
		cmd->cmd_path = get_cmd_path(input, exec, cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
	return (TRUE);
}

int	init_block_cmd(t_input *input, t_exec *exec, t_cmd **cmd, ssize_t *i)
{
	t_token	*token_array;
	int		found;

	token_array = (t_token *)input->v_tokens->array;
	found = 0;
	while (*i < input->token_qty)
	{
		if (token_array[*i].type == COMMAND)
		{
			*cmd = malloc(sizeof(t_cmd));
			if (!*cmd)
				return (-1);
			setup_block_cmd(input, exec, token_array[*i], *cmd);
			found = 1;
			break ;
		}
		++(*i);
	}
	if (!found)
		return (0);
	++(*i);
	return (1);
}
