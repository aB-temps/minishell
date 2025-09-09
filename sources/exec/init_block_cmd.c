/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:03:31 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static bool	setup_block_cmd(t_input *input, t_exec *exec, t_token token,
		t_cmd *cmd)
{
	cmd->cmd_path = NULL;
	cmd->cmd_args = (char **)token.formatted_content;
	cmd->is_builtin = is_builtin(cmd->cmd_args[0]);
	if (cmd->cmd_args[0][0] && !cmd->is_builtin)
		cmd->cmd_path = get_cmd_path(input, exec, cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
	return (true);
}

static int	find_command_in_block(t_token *token_array, int start,
		int max_tokens)
{
	int	i;

	i = start;
	while (i < max_tokens && token_array[i].type != PIPE)
	{
		if (token_array[i].type == COMMAND)
			return (i);
		i++;
	}
	return (-1);
}

int	init_block_cmd(t_input *input, t_exec *exec, t_cmd **cmd,
		ssize_t *block_index)
{
	t_token	*token_array;
	int		pipe_count;
	int		i;
	int		cmd_token_idx;

	token_array = (t_token *)input->v_tokens->array;
	pipe_count = 0;
	i = 0;
	while (i < input->token_qty && pipe_count < *block_index)
	{
		if (token_array[i].type == PIPE)
			pipe_count++;
		i++;
	}
	cmd_token_idx = find_command_in_block(token_array, i, input->token_qty);
	if (cmd_token_idx == -1)
		return (0);
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (-1);
	setup_block_cmd(input, exec, token_array[cmd_token_idx], *cmd);
	return (1);
}
