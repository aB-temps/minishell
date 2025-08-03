/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:13:28 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/03 20:26:32 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "debug.h"

size_t	count_blocks(t_token *array, ssize_t tkn_qty)
{
	ssize_t	i;
	size_t	block_qty;

	i = 0;
	block_qty = 1;
	while (i < tkn_qty)
	{
		if (array[i].type == PIPE)
			++block_qty;
		i++;
	}
	return (block_qty);
}
