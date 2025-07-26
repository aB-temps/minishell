/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:37 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:47:38 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	exp_var_strlen(char *s, t_vector *v_var_array)
{
	const t_env_var	*var_array = (t_env_var *)v_var_array->array;
	size_t			i;
	size_t			j;
	size_t			len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		if (j < v_var_array->nb_elements && !ft_strncmp(var_array[j].key, &s[i],
				ft_strlen(var_array[j].key)))
		{
			i += ft_strlen(var_array[j].key);
			len += ft_strlen(var_array[j++].value);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
