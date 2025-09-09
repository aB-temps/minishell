/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:27:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

bool	is_executable_token(t_token *array, ssize_t i)
{
	if (array[i].type >= COMMAND && array[i].type <= HEREDOC)
		return (true);
	return (false);
}
