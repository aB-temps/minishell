/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:14:35 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 00:10:01 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_blocks(t_block **block)
{
	int	i;

	i = 0;
	while (block[i])
	{
		free(block[i]->cmd);
		++i;
	}
}
