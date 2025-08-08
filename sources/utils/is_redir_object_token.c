/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_object_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:35:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:11:45 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

enum e_bool	is_redir_object_token(t_token *array, ssize_t i)
{
	if (array[i].type < COMMAND)
		return (FALSE);
	else
		return (TRUE);
}
