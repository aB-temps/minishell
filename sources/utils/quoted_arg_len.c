/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_arg_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:01:07 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 16:21:54 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"

void	quoted_arg_len(char quote, size_t *i, char *line);

void	quoted_arg_len(char quote, size_t *i, char *line)
{
	size_t	count;

	count = 0;
	while (line[++(*i)])
	{
		if (line[*i] == quote)
		{
			count++;
			while (line[*i] && (count < 2 && !is_whitespace(line[*i])))
			{
				count += (line[*i] == quote);
				(*i)++;
			}
			break ;
		}
	}
}
