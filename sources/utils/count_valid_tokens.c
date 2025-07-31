/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_valid_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:33:35 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/31 02:33:36 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	count_valid_tokens(size_t qty, const t_token *array)
{
	size_t	i;
	size_t	valid_tokens;

	i = 0;
	valid_tokens = 0;
	while (i < qty)
	{
		if (array[i].type >= COMMAND && array[i].type <= HEREDOC)
			valid_tokens++;
		i++;
	}
	return (valid_tokens);
}
