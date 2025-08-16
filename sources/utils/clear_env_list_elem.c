/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env_list_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:46:24 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:46:25 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <stdio.h>

void	clear_env_list_elem(void *var)
{
	if (var)
	{
		if (((t_env_var *)var)->key)
			free(((t_env_var *)var)->key);
		if (((t_env_var *)var)->value)
			free(((t_env_var *)var)->value);
		free(var);
	}
}
