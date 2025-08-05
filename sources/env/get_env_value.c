/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:15:26 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 16:33:18 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "token_formatting.h"

char	*get_env_value(char *var_name, t_input *input)
{
	char	*var_value;
	t_list	*tmp;

	var_value = (void *)0;
	tmp = input->env->list;
	while (tmp)
	{
		if (!ft_strncmp(var_name, ((t_env_var *)tmp->content)->key,
				ft_strlen(var_name)
				+ ft_strlen(((t_env_var *)tmp->content)->key)))
		{
			var_value = ft_strdup(((t_env_var *)tmp->content)->value);
			return (var_value);
		}
		tmp = tmp->next;
	}
	var_value = ft_strdup("");
	return (var_value);
}
