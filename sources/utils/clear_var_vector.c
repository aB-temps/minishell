/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_var_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:22 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 16:10:21 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	clear_var(t_env_var *var)
{
	if (var->key)
	{
		free(var->key);
		var->key = (void *)0;
	}
	if (var->value)
	{
		free(var->value);
		var->value = (void *)0;
	}
}

void	clear_var_vector(t_vector *v_var_array)
{
	t_env_var	*var_array;
	size_t		i;

	var_array = (t_env_var *)v_var_array->array;
	i = 0;
	while (i < v_var_array->nb_elements)
	{
		clear_var(&var_array[i]);
		i++;
	}
}
