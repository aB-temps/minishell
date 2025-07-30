/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_env_var_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:45:43 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/30 21:45:44 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

bool	is_empty_var_token(t_token *array, ssize_t i)
{
	if (!(array[i].type == ENV_VAR && !ft_strlen(array[i].formatted_content)))
		return (true);
	else
		return (false);
}
