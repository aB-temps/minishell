/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_object_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:35:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/31 02:35:21 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

bool	is_redir_object_token(t_token *array, ssize_t i)
{
	if (array[i].type < COMMAND)
		return (false);
	else
		return (true);
}
