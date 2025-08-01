/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:16 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/01 05:05:13 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "debug.h"
#include "input.h"
#include "utils.h"

void	clear_token(t_vector *tokens)
{
	const t_token	*array = (t_token *)tokens->array;
	size_t			i;

	i = 0;
	while (i < tokens->nb_elements)
	{
		if (array[i].type == COMMAND)
			free_tab_return_null((char **)array[i].formatted_content);
		else if (array[i].type == HEREDOC
			&& ft_strlen(array[i].raw_content) > 2)
		{
			safe_close(((int *)array[i].formatted_content)[0]);
			safe_close(((int *)array[i].formatted_content)[1]);
			free(array[i].formatted_content);
		}
		else
			free(array[i].formatted_content);
		free(array[i].raw_content);
		i++;
	}
}
