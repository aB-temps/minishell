/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:27:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:11:42 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

enum e_bool	is_executable_token(t_token *array, ssize_t i)
{
	if (array[i].type >= COMMAND && array[i].type <= HEREDOC)
		return (TRUE);
	return (FALSE);
}
