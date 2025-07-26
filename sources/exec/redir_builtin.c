/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:05:21 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/24 17:05:56 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "input.h"
// #include <stdio.h>

void	apply_redirections_builtin(t_input *input, int *old_stdout,
		int *old_stdint)
{
	t_token *tokens_array;
	int i;
	int fd;
	int cmd_count;

	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	cmd_count = 0;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
		{
			i++;
			while (i < input->token_qty && tokens_array[i].type != COMMAND)
			{
				if (tokens_array[i].type == REDIR_OUT)
				{
					if (*old_stdout == -1)
						*old_stdout = dup(STDOUT_FILENO);
					fd = open(tokens_array[i].formatted_content,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd != -1)
					{
						dup2(fd, STDOUT_FILENO);
						close(fd);
					}
				}
				else if (tokens_array[i].type == APPEND)
				{
					if (*old_stdout == -1)
						*old_stdout = dup(STDOUT_FILENO);
					fd = open(tokens_array[i].formatted_content,
							O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd != -1)
					{
						dup2(fd, STDOUT_FILENO);
						close(fd);
					}
				}
				else if (tokens_array[i].type == REDIR_IN)
				{
					if (*old_stdint == -1)
						*old_stdint = dup(STDIN_FILENO);
					fd = open((char *)tokens_array[i].formatted_content,
							O_RDONLY);
					if (fd != -1)
					{
						dup2(fd, STDIN_FILENO);
						close(fd);
					}
				}
				else if (tokens_array[i].type == HEREDOC)
				{
					if (*old_stdint == -1)
						*old_stdint = dup(STDIN_FILENO);
					dup2(STDIN_FILENO,
						((int *)tokens_array[i].formatted_content)[1]);
					close(STDIN_FILENO);
				}
				i++;
				break ;
			}
			cmd_count++;
		}
		i++;
	}
}