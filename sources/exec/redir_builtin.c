/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:05:21 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/27 17:26:07 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "input.h"
#include <stdio.h>

static void	handle_heredoc_builtin(int *old_stdin, t_token *tok_array, int i)
{
	if (*old_stdin == -1)
		*old_stdin = dup(STDIN_FILENO);
	dup2(STDIN_FILENO, ((int *)tok_array[i].formatted_content)[1]);
	close(STDIN_FILENO);
}

static void	handle_redir_in_builtin(int *old_stdin, t_token *tok_array, int fd,
		int i)
{
	if (*old_stdin == -1)
		*old_stdin = dup(STDIN_FILENO);
	fd = open((char *)tok_array[i].formatted_content, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	handle_redir_append_builtin(int *old_stdout, t_token *tok_array,
		int fd, int i)
{
	if (*old_stdout == -1)
		*old_stdout = dup(STDOUT_FILENO);
	fd = open(tok_array[i].formatted_content, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static void	handle_redir_out_builtin(int *old_stdout, t_token *tok_array,
		int fd, int i)
{
	if (*old_stdout == -1)
		*old_stdout = dup(STDOUT_FILENO);
	fd = open(tok_array[i].formatted_content, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
void	apply_redirections_builtin(t_input *input, int *old_stdout,
		int *old_stdin)
{
	t_token	*tok_array;
	int		i;
	int		fd;

	fd = 0;
	tok_array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (tok_array[i].type == COMMAND)
		{
			i++;
			while (i < input->token_qty && tok_array[i].type != COMMAND)
			{
				if (tok_array[i].type == REDIR_OUT)
					handle_redir_out_builtin(old_stdout, tok_array, fd, i);
				else if (tok_array[i].type == APPEND)
					handle_redir_append_builtin(old_stdout, tok_array, fd, i);
				else if (tok_array[i].type == REDIR_IN)
					handle_redir_in_builtin(old_stdin, tok_array, fd, i);
				else if (tok_array[i].type == HEREDOC)
					handle_heredoc_builtin(old_stdin, tok_array, i);
				i++;
				break ;
			}
		}
		i++;
	}
}
