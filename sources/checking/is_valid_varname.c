/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_varname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:07:38 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/30 15:11:55 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"
#include <stdio.h>

enum e_bool	is_valid_varname(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalpha(s[i]) || s[i] == '_'))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(s, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
