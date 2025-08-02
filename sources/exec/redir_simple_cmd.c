/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:16:58 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/02 15:35:48 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_redir_in(t_exec *exec, t_token current_token)
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

int	handle_redir_out(t_exec *exec, t_token current_token)
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
