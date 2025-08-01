/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/01 05:02:43 by enchevri         ###   ########lyon.fr   */
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
