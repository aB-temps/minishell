/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:14:19 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 11:06:13 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

void	init_io_fds(t_token *array, t_block block, ssize_t tkn_qty)
{
	ssize_t	i;

	i = 0;
	while (i < tkn_qty)
	{
		block.io_fds[0] = -1;
		block.io_fds[1] = -1;
		while (i < tkn_qty && array[i].type != PIPE)
		{
			if (array[i].type >= REDIR_IN && array[i].type <= HEREDOC)
			{
				if (array[i].type == REDIR_IN)
				{
					if (block.io_fds[0] != STDIN_FILENO)
						safe_close(block.io_fds[0]);
					block.io_fds[0] = open((char *)array[i].formatted_content,
							O_RDONLY | 0644);
				}
				else if (array[i].type == HEREDOC)
				{
					if (block.io_fds[0] != STDIN_FILENO)
						safe_close(block.io_fds[0]);
					block.io_fds[0] = ((int *)array[i].formatted_content)[1];
				}
				else if (array[i].type == REDIR_OUT)
				{
					if (block.io_fds[1] != STDOUT_FILENO)
						safe_close(block.io_fds[1]);
					block.io_fds[1] = open((char *)array[i].formatted_content,
							O_WRONLY | O_CREAT | 0644);
				}
				else if (array[i].type == APPEND)
				{
					if (block.io_fds[1] != STDOUT_FILENO)
						safe_close(block.io_fds[1]);
					block.io_fds[1] = open((char *)array[i].formatted_content,
							O_WRONLY | O_APPEND | O_CREAT | 0644);
				}
			}
			i++;
		}
		i++;
	}
}

// bool	init_block_array(t_block **block, size_t *block_qty, t_input *input)
// {
// 	t_token	*array;

// 	array = (t_token *)input->v_tokens->array;
// 	*block_qty = count_blocks((t_token *)input->v_tokens->array,
// 			input->token_qty);
// 	(*block) = malloc(sizeof(t_block) * ((*block_qty) + 1));
// 	if (!*block)
// 		return (false);
// 	if (!init_cmd(input, *block))
// 	{
// 		free(block);
// 		return (false);
// 	}
// 	init_io_fds(array, *block, input->token_qty);
// 	// set_block_type(input, *block);
// 	return (true);
// }
