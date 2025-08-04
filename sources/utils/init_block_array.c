/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:14:19 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 15:40:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

// int	init_fd_and_type(t_block *block)
// {
// }

bool	init_block_array(t_block **block, size_t *block_qty, t_input *input)
{
	*block_qty = count_blocks((t_token *)input->v_tokens->array,
			input->token_qty);
	(*block) = malloc(sizeof(t_block) * ((*block_qty) + 1));
	if (!*block)
		return (false);
	if (init_cmd(input, *block) == false)
	{
		free(block);
		return (false);
	}
	// init_io_fds(*block);
	return (true);
}
