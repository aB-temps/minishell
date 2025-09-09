/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_in_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:37:59 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static bool	handle_redir_in(t_exec *exec, t_token current_token)
{
	int	fd_temp;

	if (current_token.type == REDIR_IN)
	{
		fd_temp = open(current_token.formatted_content, O_RDONLY);
		if (fd_temp == -1)
		{
			perror(current_token.formatted_content);
			return (false);
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
	return (true);
}

static bool	handle_redir_out(t_exec *exec, t_token current_token)
{
	int	flags;
	int	fd_temp;

	if (current_token.type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd_temp = open((char *)current_token.formatted_content, flags, 0644);
	if (fd_temp == -1)
	{
		perror((char *)current_token.formatted_content);
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

static bool	handle_redirs_in_block(t_token *token_array, t_exec *exec,
		int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
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

bool	create_files_in_block(t_input *input, t_exec *exec, ssize_t cmd_nb)
{
	int		pipe_count;
	int		i;
	int		start;
	t_token	*token_array;

	token_array = (t_token *)input->v_tokens->array;
	pipe_count = 0;
	i = 0;
	while (i < input->token_qty && pipe_count < cmd_nb)
		if (token_array[i++].type == PIPE)
			pipe_count++;
	start = i;
	while (i < input->token_qty && token_array[i].type != PIPE)
		i++;
	return (handle_redirs_in_block(token_array, exec, start, i));
}
