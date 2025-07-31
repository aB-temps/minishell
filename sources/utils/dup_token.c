/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:46:27 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/31 22:35:33 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

t_token	dup_token(t_token token)
{
	t_token	new_token;

	init_token(&new_token);
	new_token.type = token.type;
	new_token.link_to_next = token.link_to_next;
	new_token.raw_content = ft_strdup(token.raw_content);
	if (!new_token.raw_content)
	{
		new_token.type = -1;
		return (new_token);
	}
	if (token.type == COMMAND)
		new_token.formatted_content = ft_tabdup(token.formatted_content);
	else
	{
		new_token.formatted_content = ft_strdup(token.formatted_content);
	}
	if (!new_token.formatted_content)
		new_token.type = -1;
	return (new_token);
}
