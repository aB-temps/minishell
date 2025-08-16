/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_env_var_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:45:43 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:11:46 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

enum e_bool	is_empty_var_token(t_token *array, ssize_t i)
{
	if (!(array[i].type == ENV_VAR && !ft_strlen(array[i].formatted_content)))
		return (TRUE);
	else
		return (FALSE);
}
