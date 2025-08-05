/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:23 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 01:50:05 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	tokenize_input(t_input *input, char *line)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator(line[i]))
			tokenize_operator(input, &i, line, line_len);
		else if (is_quote(line[i]))
			tokenize_quote(input, &i, line);
		else
			tokenize_word(input, &i, line);
	}
}
