/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:35:43 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:36:27 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

size_t	count_command_args(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	j;
	size_t	count;

	j = *i;
	count = 0;
	while (j + 1 <= input->token_qty && array[j].type != PIPE)
	{
		if (!(array[j].type >= REDIR_IN && array[j].type <= HEREDOC))
			count++;
		j++;
	}
	return (count);
}
