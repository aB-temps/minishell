/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_in_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:37:59 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 20:29:40 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include <fcntl.h>
#include <stdio.h>

static int	handle_redir_in(t_exec *exec, t_token current_token)
{
	int	fd_temp;

	if (current_token.type == REDIR_IN)
	{
		fd_temp = open(current_token.formatted_content, O_RDONLY);
		if (fd_temp == -1)
		{
			perror(current_token.formatted_content);
			return (1);
		}
		else
		{
			if (exec->block.io_fds[0] != -1)
				close(exec->block.io_fds[0]);
			exec->block.io_fds[0] = fd_temp;
		}
	}
	else
	{
		if (exec->block.io_fds[0] != -1)
			close(exec->block.io_fds[0]);
		exec->block.io_fds[0] = ((int *)current_token.formatted_content)[1];
	}
	return (0);
}

static bool	handle_redir_out(t_exec *exec, t_token current_token)
{
	int	flags;
	int	fd_temp;

	if (current_token.type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd_temp = open(current_token.formatted_content, flags, 0644);
	if (fd_temp == -1)
	{
		perror(current_token.formatted_content);
		return (false);
	}
	else
	{
		if (exec->block.io_fds[1] != -1)
			close(exec->block.io_fds[1]);
		exec->block.io_fds[1] = fd_temp;
	}
	return (true);
}

static int	search_cmd_by_index(t_input *input, t_token *token_array,
		int searched_n_cmd)
{
	int	cmd_count;
	int	i;

	cmd_count = -1;
	i = 0;
	while (i < input->token_qty)
	{
		if (token_array[i].type == COMMAND)
		{
			cmd_count++;
			if (cmd_count == searched_n_cmd)
				break ;
		}
		i++;
	}
	if (i >= input->token_qty)
		return (-1);
	while (i >= 0 && token_array[i].type != PIPE)
		i--;
	return (i);
}

bool	create_files_in_block(t_input *input, t_exec *exec, ssize_t cmd_nb)
{
	int		i;
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	i = search_cmd_by_index(input, token_array, cmd_nb);
	if (i != 0)
		i++;
	while (i < input->token_qty)
	{
		if (token_array[i].type == PIPE)
			return (0);
		if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
		{
			if (!handle_redir_out(exec, token_array[i]))
				return (false);
		}
		else if (token_array[i].type == REDIR_IN
			|| token_array[i].type == HEREDOC)
		{
			if (!handle_redir_in(exec, token_array[i]))
				return (false);
		}
		i++;
	}
	return (true);
}
