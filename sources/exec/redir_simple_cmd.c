/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:16:58 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/30 18:29:21 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
			if (exec->fd_infile != -1)
				close(exec->fd_infile);
			exec->fd_infile = fd_temp;
		}
	}
	else
	{
		if (exec->fd_infile != -1)
			close(exec->fd_infile);
		exec->fd_infile = ((int *)current_token.formatted_content)[1];
	}
	return (0);
}

static int	handle_redir_out(t_exec *exec, t_token current_token)
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
		return (1);
	}
	else
	{
		if (exec->fd_outfile != -1)
			close(exec->fd_outfile);
		exec->fd_outfile = fd_temp;
	}
	return (0);
}

int	search_cmd_by_index(t_input *input, t_token *token_array,
		int searched_n_cmd)
{
	int	cmd_index;
	int	i;

	i = 0;
	cmd_index = 0;
	if (searched_n_cmd == 0)
		return (0);
	while (i < input->token_qty)
	{
		while (i < input->token_qty && token_array[i].type != PIPE)
			i++;
		if (++cmd_index == searched_n_cmd)
			return (i);
		i++;
	}
	return (-1);
}

int	create_all_files(t_exec *exec, t_input *input, t_token *token_array,
		int cmd_nb)
{
	int	i;

	i = search_cmd_by_index(input, token_array, cmd_nb);
	if (i != 0)
		i++;
	while (i < input->token_qty)
	{
		if (token_array[i].type == PIPE)
			return (0);
		if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
		{
			if (handle_redir_out(exec, token_array[i]))
				return (2);
		}
		else if (token_array[i].type == REDIR_IN
			|| token_array[i].type == HEREDOC)
		{
			if (handle_redir_in(exec, token_array[i]))
				return (2);
		}
		i++;
	}
	return (0);
}
