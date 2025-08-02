/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:05:21 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:54 by abetemps         ###   ########.fr       */
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

static void	handle_redir_in_builtin(int *old_stdin, t_token *tok_array, int i)
{
	int	fd_temp;

	if (*old_stdin == -1)
		*old_stdin = dup(STDIN_FILENO);
	fd_temp = open((char *)tok_array[i].formatted_content, O_RDONLY);
	if (fd_temp != -1)
	{
		dup2(fd_temp, STDIN_FILENO);
		close(fd_temp);
	}
}

static void	handle_redir_append_builtin(int *old_stdout, t_token *tok_array,
		int i)
{
	int	fd_temp;

	if (*old_stdout == -1)
		*old_stdout = dup(STDOUT_FILENO);
	fd_temp = open(tok_array[i].formatted_content,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_temp != -1)
	{
		dup2(fd_temp, STDOUT_FILENO);
		close(fd_temp);
	}
}

static void	handle_redir_out_minishell(int *old_stdout, t_token *tok_array,
		int i)
{
	int	fd_temp;

	if (*old_stdout == -1)
		*old_stdout = dup(STDOUT_FILENO);
	fd_temp = open(tok_array[i].formatted_content, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd_temp != -1)
	{
		dup2(fd_temp, STDOUT_FILENO);
		close(fd_temp);
	}
}

void	apply_redirections_builtin(t_input *input, int *old_stdout,
		int *old_stdin)
{
	t_token	*tok_array;
	int		i;

	tok_array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (tok_array[i].type == COMMAND)
		{
			while (++i < input->token_qty && tok_array[i].type != COMMAND)
			{
				if (tok_array[i].type == REDIR_OUT)
					handle_redir_out_minishell(old_stdout, tok_array, i);
				else if (tok_array[i].type == APPEND)
					handle_redir_append_builtin(old_stdout, tok_array, i);
				else if (tok_array[i].type == REDIR_IN)
					handle_redir_in_builtin(old_stdin, tok_array, i);
				else if (tok_array[i].type == HEREDOC)
					handle_heredoc_builtin(old_stdin, tok_array, i);
			}
		}
		else
			i++;
	}
}
